/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * istream.c
 *
 * Copyright (C) 2019 David Oberhollenzer <goliath@infraroot.at>
 */
#include "../internal.h"

typedef struct {
	istream_t base;
	char *path;
	int fd;

	bool eof;
	size_t buffer_offset;
	size_t buffer_used;
	sqfs_u8 buffer[BUFSZ];
} file_istream_t;

static int precache(istream_t *strm)
{
	file_istream_t *file = (file_istream_t *)strm;

	if (file->eof)
		return 0;

	if (file->buffer_offset > 0 &&
	    file->buffer_offset < file->buffer_used) {
		memmove(file->buffer, file->buffer + file->buffer_offset,
			file->buffer_used - file->buffer_offset);
	}

	file->buffer_used -= file->buffer_offset;
	file->buffer_offset = 0;

	while (file->buffer_used < BUFSZ) {
		ssize_t ret = read(file->fd, file->buffer + file->buffer_used,
				   BUFSZ - file->buffer_used);

		if (ret == 0) {
			file->eof = true;
			break;
		}

		if (ret < 0) {
			if (errno == EINTR)
				continue;

			perror(file->path);
			return -1;
		}

		file->buffer_used += ret;
	}

	return 0;
}

static int file_get_buffered_data(istream_t *strm, const sqfs_u8 **out,
				  size_t *size, size_t want)
{
	file_istream_t *file = (file_istream_t *)strm;

	if (want > BUFSZ)
		want = BUFSZ;

	if (file->buffer_used == 0 ||
	    (file->buffer_used - file->buffer_offset) < want) {
		int ret = precache(strm);
		if (ret)
			return ret;
	}

	*out = file->buffer + file->buffer_offset;
	*size = file->buffer_used - file->buffer_offset;
	return (file->eof && *size == 0) ? 1 : 0;
}

static void file_advance_buffer(istream_t *strm, size_t count)
{
	file_istream_t *file = (file_istream_t *)strm;

	assert(count <= file->buffer_used);

	file->buffer_offset += count;

	assert(file->buffer_offset <= file->buffer_used);
}

static const char *file_get_filename(istream_t *strm)
{
	file_istream_t *file = (file_istream_t *)strm;

	return file->path;
}

static void file_destroy(sqfs_object_t *obj)
{
	file_istream_t *file = (file_istream_t *)obj;

	if (file->fd != STDIN_FILENO)
		close(file->fd);

	free(file->path);
	free(file);
}

istream_t *istream_open_file(const char *path)
{
	file_istream_t *file = calloc(1, sizeof(*file));
	istream_t *strm = (istream_t *)file;

	if (file == NULL) {
		perror(path);
		return NULL;
	}

	sqfs_object_init(file, file_destroy, NULL);

	file->path = strdup(path);
	if (file->path == NULL) {
		perror(path);
		goto fail_free;
	}

	file->fd = open(path, O_RDONLY);
	if (file->fd < 0) {
		perror(path);
		goto fail_path;
	}

	strm->get_buffered_data = file_get_buffered_data;
	strm->advance_buffer = file_advance_buffer;
	strm->get_filename = file_get_filename;
	return strm;
fail_path:
	free(file->path);
fail_free:
	free(file);
	return NULL;
}

istream_t *istream_open_stdin(void)
{
	file_istream_t *file = calloc(1, sizeof(*file));
	istream_t *strm = (istream_t *)file;

	if (file == NULL)
		goto fail;

	sqfs_object_init(file, file_destroy, NULL);

	file->path = strdup("stdin");
	if (file->path == NULL)
		goto fail;

	file->fd = STDIN_FILENO;
	strm->get_buffered_data = file_get_buffered_data;
	strm->advance_buffer = file_advance_buffer;
	strm->get_filename = file_get_filename;
	return strm;
fail:
	perror("creating file wrapper for stdin");
	free(file);
	return NULL;
}
