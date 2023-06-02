/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * xfrm.c
 *
 * Copyright (C) 2022 David Oberhollenzer <goliath@infraroot.at>
 */
#include "xfrm/compress.h"
#include "xfrm/stream.h"
#include "util/test.h"
#include "io/xfrm.h"
#include "io/mem.h"

static const sqfs_u8 blob_in[] = {
#if defined(DO_XZ)
	0xfd, 0x37, 0x7a, 0x58, 0x5a, 0x00, 0x00, 0x00,
	0xff, 0x12, 0xd9, 0x41, 0x02, 0x00, 0x21, 0x01,
	0x1c, 0x00, 0x00, 0x00, 0x10, 0xcf, 0x58, 0xcc,
	0xe0, 0x01, 0xbd, 0x01, 0x43, 0x5d, 0x00, 0x26,
	0x1b, 0xca, 0x46, 0x67, 0x5a, 0xf2, 0x77, 0xb8,
	0x7d, 0x86, 0xd8, 0x41, 0xdb, 0x05, 0x35, 0xcd,
	0x83, 0xa5, 0x7c, 0x12, 0xa5, 0x05, 0xdb, 0x90,
	0xbd, 0x2f, 0x14, 0xd3, 0x71, 0x72, 0x96, 0xa8,
	0x8a, 0x7d, 0x84, 0x56, 0x71, 0x8d, 0x6a, 0x22,
	0x98, 0xab, 0x9e, 0x3d, 0xc3, 0x55, 0xef, 0xcc,
	0xa5, 0xc3, 0xdd, 0x5b, 0x8e, 0xbf, 0x03, 0x81,
	0x21, 0x40, 0xd6, 0x26, 0x91, 0x02, 0x45, 0x4e,
	0x20, 0x91, 0xcf, 0x8c, 0x51, 0x22, 0x02, 0x70,
	0xba, 0x05, 0x6b, 0x83, 0xef, 0x3f, 0x8e, 0x09,
	0xef, 0x88, 0xf5, 0x37, 0x1b, 0x89, 0x8d, 0xff,
	0x1e, 0xee, 0xe8, 0xb0, 0xac, 0xf2, 0x6e, 0xd4,
	0x3e, 0x25, 0xaf, 0xa0, 0x6d, 0x2e, 0xc0, 0x7f,
	0xb5, 0xa0, 0xcb, 0x90, 0x1f, 0x08, 0x1a, 0xe2,
	0x90, 0x20, 0x19, 0x71, 0x0c, 0xe8, 0x3f, 0xe5,
	0x39, 0xeb, 0x9a, 0x62, 0x4f, 0x06, 0xda, 0x3c,
	0x32, 0x59, 0xcc, 0x83, 0xe3, 0x83, 0x0f, 0x38,
	0x7d, 0x43, 0x37, 0x6c, 0x0b, 0x05, 0x65, 0x98,
	0x25, 0xdb, 0xf2, 0xc0, 0x2d, 0x39, 0x36, 0x5d,
	0xd4, 0xb6, 0xc2, 0x79, 0x73, 0x3e, 0xc2, 0x6e,
	0x54, 0xec, 0x78, 0x2b, 0x5d, 0xf1, 0xd1, 0xb4,
	0xb3, 0xcd, 0xf3, 0x89, 0xf5, 0x81, 0x3e, 0x2c,
	0x65, 0xd6, 0x73, 0xd3, 0x1b, 0x20, 0x68, 0x0c,
	0x93, 0xd4, 0xfc, 0x9f, 0xf8, 0xa7, 0xd4, 0xfa,
	0x3a, 0xb1, 0x13, 0x93, 0x4b, 0xec, 0x78, 0x7d,
	0x5c, 0x81, 0x80, 0xe5, 0x14, 0x78, 0xfe, 0x7e,
	0xde, 0xf7, 0xad, 0x9e, 0x84, 0xba, 0xf1, 0x00,
	0xe9, 0xbd, 0x2c, 0xf4, 0x70, 0x7d, 0xbe, 0x29,
	0xb9, 0xf0, 0x10, 0xb9, 0x01, 0xf1, 0x76, 0x8a,
	0x5a, 0xad, 0x02, 0xa1, 0x32, 0xc8, 0x53, 0x59,
	0x11, 0x4c, 0xe2, 0x98, 0x34, 0xd9, 0x23, 0x51,
	0x4a, 0x40, 0x2b, 0x87, 0x41, 0xdd, 0x50, 0xcd,
	0x98, 0x1e, 0x29, 0x86, 0x23, 0x93, 0x3e, 0x9b,
	0x6b, 0x16, 0xa1, 0x40, 0xac, 0xe7, 0x40, 0xfe,
	0xa9, 0x87, 0x48, 0x25, 0x52, 0x02, 0x8b, 0xc4,
	0x68, 0x08, 0x5a, 0x62, 0xc1, 0xb2, 0x07, 0x3b,
	0x26, 0x1e, 0x59, 0x5c, 0x47, 0x24, 0xae, 0x8e,
	0xe5, 0xf7, 0xe6, 0x4b, 0x13, 0xb4, 0x6d, 0x46,
	0x65, 0x4f, 0xd0, 0x48, 0xcc, 0x51, 0x4b, 0x80,
	0xcb, 0xf1, 0xd4, 0x6c, 0x45, 0x98, 0x92, 0x47,
	0xeb, 0x60, 0x00, 0x00, 0x00, 0x01, 0xd7, 0x02,
	0xbe, 0x03, 0x00, 0x00, 0xda, 0x2c, 0x45, 0x49,
	0xa8, 0x00, 0x0a, 0xfc, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x59, 0x5a
#elif defined(DO_BZIP2)
	0x42, 0x5a, 0x68, 0x39, 0x31, 0x41, 0x59, 0x26,
	0x53, 0x59, 0x05, 0x24, 0x28, 0x04, 0x00, 0x00,
	0x27, 0xd7, 0x80, 0x00, 0x10, 0x40, 0x05, 0x06,
	0x04, 0x02, 0x00, 0x3f, 0xe7, 0xff, 0x40, 0x30,
	0x01, 0x2d, 0x23, 0x62, 0x26, 0x05, 0x3d, 0x03,
	0x54, 0xfd, 0x53, 0x4c, 0x86, 0x9e, 0x90, 0x6a,
	0x9e, 0x9e, 0x85, 0x3c, 0xa0, 0x00, 0x00, 0x1a,
	0x9e, 0x41, 0x13, 0x13, 0x28, 0x69, 0x03, 0xd4,
	0x0f, 0x1c, 0x70, 0xd0, 0xb4, 0xe3, 0xe4, 0x75,
	0x4e, 0x8b, 0x67, 0x43, 0x7b, 0x38, 0x27, 0x77,
	0xe4, 0xc1, 0x98, 0x3a, 0x2d, 0x3a, 0xe4, 0x44,
	0x98, 0xdc, 0x49, 0x8b, 0x22, 0x48, 0xfc, 0xc8,
	0xe7, 0x57, 0x05, 0x3c, 0x5a, 0xee, 0x5a, 0x84,
	0xcd, 0x7c, 0x8f, 0x26, 0x6b, 0x6e, 0xf7, 0xb5,
	0x49, 0x1f, 0x79, 0x42, 0x5d, 0x09, 0x8c, 0xc6,
	0xde, 0x0c, 0x0d, 0xb1, 0x46, 0xb4, 0xee, 0xd9,
	0x8f, 0x33, 0x37, 0x04, 0xa9, 0x05, 0x49, 0xe3,
	0x04, 0x16, 0x62, 0x36, 0x3a, 0x01, 0xda, 0xd4,
	0xc8, 0x8a, 0x32, 0x02, 0x1f, 0x62, 0x4b, 0xa4,
	0x49, 0x59, 0xda, 0x50, 0x85, 0x69, 0x35, 0x21,
	0x10, 0xc6, 0x8a, 0x3c, 0x44, 0x95, 0xb0, 0xbc,
	0xc5, 0x6b, 0xea, 0xfb, 0x40, 0xbd, 0x14, 0x01,
	0x6a, 0xfa, 0xcd, 0x67, 0xd8, 0x2d, 0x93, 0x8b,
	0xda, 0x44, 0x1b, 0xe9, 0x5a, 0x87, 0x60, 0xb0,
	0xe0, 0x73, 0xd1, 0x01, 0x3a, 0x66, 0x05, 0xcc,
	0x34, 0xa0, 0x63, 0x8d, 0x35, 0x5e, 0xa0, 0x9f,
	0x05, 0x89, 0x15, 0x51, 0x48, 0x16, 0x0c, 0x61,
	0xf4, 0x30, 0xb8, 0x07, 0x29, 0xc0, 0xf5, 0x1a,
	0xe1, 0x0d, 0x6c, 0xfe, 0x91, 0xda, 0x13, 0x2f,
	0x8e, 0x5b, 0x1c, 0xfc, 0xb3, 0xb2, 0x30, 0x9d,
	0xf6, 0x09, 0x30, 0x55, 0x30, 0x67, 0xc2, 0x87,
	0xe9, 0x9a, 0xd4, 0x1d, 0x66, 0x11, 0x54, 0x89,
	0x21, 0xe1, 0x55, 0x84, 0xbf, 0xa6, 0x11, 0xa4,
	0xb8, 0x40, 0xed, 0x42, 0x20, 0xb9, 0xb7, 0x26,
	0x31, 0x14, 0x4f, 0x86, 0xdc, 0x50, 0x34, 0x38,
	0x8b, 0x57, 0x77, 0x21, 0xf6, 0x89, 0xbd, 0xc5,
	0x65, 0xc3, 0x23, 0x45, 0xec, 0x7f, 0x8b, 0xb9,
	0x22, 0x9c, 0x28, 0x48, 0x02, 0x92, 0x14, 0x02,
	0x00,
#elif defined(DO_GZIP)
	0x1f, 0x8b, 0x08, 0x08, 0xdb, 0xa1, 0x97, 0x63,
	0x00, 0x03, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74,
	0x78, 0x74, 0x00, 0x35, 0x90, 0xc1, 0x71, 0x43,
	0x31, 0x08, 0x44, 0xef, 0xbf, 0x8a, 0x2d, 0x20,
	0xf3, 0xab, 0x48, 0x6e, 0xb9, 0xa6, 0x00, 0x82,
	0xb0, 0xc3, 0x8c, 0x24, 0x64, 0x09, 0x3c, 0x2e,
	0x3f, 0xc8, 0x4e, 0x6e, 0x42, 0xc0, 0xb2, 0xfb,
	0x3e, 0x6d, 0x4a, 0x83, 0x8e, 0x15, 0x0d, 0xc5,
	0xaa, 0x4d, 0x2c, 0x75, 0x50, 0x13, 0x7f, 0x03,
	0x5b, 0x5f, 0xc2, 0x2e, 0x1e, 0x13, 0x54, 0x74,
	0xe8, 0x62, 0xed, 0x57, 0x48, 0xd5, 0x6c, 0x2e,
	0x29, 0xb9, 0x00, 0xd1, 0x58, 0xcd, 0xca, 0xe1,
	0xd2, 0x46, 0x2e, 0x6b, 0x67, 0x2d, 0x5a, 0xa2,
	0x3b, 0xc2, 0x51, 0xe9, 0x3b, 0xe5, 0x21, 0xfe,
	0x92, 0x16, 0x34, 0xba, 0x76, 0x02, 0x55, 0xbd,
	0x05, 0x9d, 0xf8, 0x72, 0x48, 0xd7, 0x96, 0xda,
	0x68, 0xba, 0x1f, 0xf7, 0x2c, 0xa9, 0xbd, 0x1d,
	0xb7, 0xd0, 0x85, 0x6e, 0xcb, 0x67, 0x14, 0xc8,
	0x43, 0x26, 0xab, 0x93, 0xab, 0x75, 0x44, 0xad,
	0xd4, 0xd8, 0x5e, 0xca, 0x7b, 0x48, 0x97, 0xee,
	0x4b, 0x4f, 0x49, 0x1d, 0x39, 0x0c, 0xa1, 0x34,
	0xde, 0xd2, 0x93, 0x1d, 0xcf, 0x00, 0x79, 0xca,
	0x4f, 0xbc, 0x6f, 0x49, 0x0a, 0x17, 0xe8, 0x8c,
	0x74, 0xf2, 0xca, 0xaa, 0x1d, 0x53, 0xc6, 0x94,
	0x1f, 0xe9, 0x45, 0x66, 0x06, 0xcf, 0x8f, 0xbb,
	0xd5, 0x18, 0x79, 0x4e, 0xd2, 0x4e, 0x26, 0x85,
	0xac, 0x25, 0x07, 0x6b, 0xad, 0xff, 0x84, 0x32,
	0x50, 0xe0, 0x12, 0x57, 0x25, 0x47, 0xdf, 0x86,
	0x30, 0x68, 0x66, 0x11, 0xf3, 0xc4, 0xc7, 0x83,
	0x65, 0xb8, 0xc4, 0xc6, 0x98, 0x0c, 0x8c, 0x99,
	0x84, 0x73, 0x8e, 0x63, 0x68, 0x21, 0xdf, 0x1b,
	0xd6, 0x8f, 0x31, 0x4d, 0x8b, 0xf4, 0x4d, 0x71,
	0x93, 0xca, 0xa3, 0x1c, 0x75, 0x10, 0x32, 0x02,
	0xec, 0x72, 0x51, 0x56, 0x42, 0x91, 0x25, 0x73,
	0x77, 0x9b, 0xd5, 0x6d, 0x83, 0x36, 0x20, 0x4d,
	0x1c, 0xeb, 0x8f, 0x6b, 0xb4, 0xf3, 0xf8, 0x05,
	0x6b, 0x8b, 0x8b, 0x20, 0xbe, 0x01, 0x00, 0x00,
#elif defined(DO_ZSTD)
	0x28, 0xb5, 0x2f, 0xfd, 0x04, 0x88, 0xa5, 0x08,
	0x00, 0x46, 0x97, 0x3a, 0x1a, 0x80, 0x37, 0xcd,
	0x01, 0xc0, 0x8a, 0xec, 0xfe, 0x2d, 0xf2, 0xb9,
	0x44, 0x6b, 0xb9, 0x24, 0x77, 0x56, 0x5a, 0x33,
	0x17, 0x0b, 0x67, 0x83, 0x2e, 0x47, 0x07, 0x31,
	0x00, 0x32, 0x00, 0x33, 0x00, 0xc5, 0x2c, 0x5a,
	0x92, 0x93, 0x0f, 0x7b, 0xd1, 0x1d, 0x63, 0x2c,
	0xc8, 0x99, 0x94, 0x77, 0x8f, 0x94, 0x38, 0x75,
	0x80, 0x2f, 0xae, 0xc1, 0x3e, 0xd2, 0xcf, 0x49,
	0x15, 0x25, 0x1a, 0x87, 0x93, 0xdd, 0xe8, 0x00,
	0x6d, 0xaa, 0xf8, 0x54, 0x74, 0xe5, 0x48, 0x4d,
	0xa6, 0xf3, 0x1a, 0xa3, 0x13, 0x08, 0xe5, 0x26,
	0xdc, 0x73, 0xcc, 0x3e, 0xfd, 0x86, 0xa9, 0x52,
	0xb2, 0x76, 0xc7, 0xc2, 0x0f, 0xe4, 0x84, 0x4b,
	0x12, 0x61, 0x3a, 0x6b, 0x7a, 0x1e, 0x8a, 0x81,
	0xa9, 0x9b, 0x11, 0x37, 0x25, 0x55, 0x73, 0x73,
	0x71, 0xa0, 0x84, 0xca, 0xc3, 0x4b, 0xb5, 0xcc,
	0x50, 0xa6, 0x46, 0xd7, 0xe8, 0x08, 0xaa, 0x04,
	0x28, 0xb1, 0x8e, 0xea, 0xb4, 0x4a, 0x49, 0x2b,
	0xd6, 0x0d, 0x59, 0x68, 0xda, 0x64, 0x29, 0x1f,
	0x85, 0x53, 0x72, 0xf1, 0xc5, 0x88, 0x1a, 0x0b,
	0x4f, 0x96, 0x43, 0xe0, 0x91, 0x89, 0xb9, 0xc0,
	0xe8, 0x18, 0xd5, 0x6e, 0x94, 0xe8, 0x35, 0x66,
	0x01, 0x94, 0x80, 0x95, 0x87, 0xe2, 0xc8, 0x19,
	0x73, 0xa3, 0x01, 0x05, 0xc1, 0x64, 0x72, 0xc9,
	0x6b, 0x6e, 0x55, 0x7c, 0x29, 0x67, 0x90, 0x93,
	0x49, 0xeb, 0xe3, 0x85, 0xc2, 0xf5, 0x79, 0x68,
	0x9d, 0x92, 0xc3, 0x32, 0x75, 0x80, 0x66, 0xf2,
	0x43, 0xa7, 0xb0, 0xc3, 0x22, 0x3f, 0x39, 0x8a,
	0x35, 0x5c, 0x63, 0x5c, 0xd1, 0x9e, 0x8a, 0xd2,
	0x78, 0x3c, 0x12, 0x01, 0x25, 0x04, 0x0e, 0x08,
	0x10, 0x88, 0xb6, 0x1b, 0xb7, 0x96, 0x35, 0xa8,
	0x0d, 0x1e, 0xae, 0xac, 0x4a, 0x70, 0xa5, 0x31,
	0xd0, 0x0c, 0x78, 0xbf, 0xdd, 0xc5, 0x24, 0x3e,
	0xcb, 0x0a, 0x0a, 0x69, 0x40, 0xba, 0xb0, 0xc4,
	0x2a, 0x9b, 0x1e, 0x0a, 0x51, 0xa6, 0x16, 0x98,
	0x76,
#endif
};

static const sqfs_u8 blob_in_concat[] = {
#if defined(DO_XZ)
	0xfd, 0x37, 0x7a, 0x58, 0x5a, 0x00, 0x00, 0x04,
	0xe6, 0xd6, 0xb4, 0x46, 0x02, 0x00, 0x21, 0x01,
	0x16, 0x00, 0x00, 0x00, 0x74, 0x2f, 0xe5, 0xa3,
	0xe0, 0x00, 0xdc, 0x00, 0xb3, 0x5d, 0x00, 0x26,
	0x1b, 0xca, 0x46, 0x67, 0x5a, 0xf2, 0x77, 0xb8,
	0x7d, 0x86, 0xd8, 0x41, 0xdb, 0x05, 0x35, 0xcd,
	0x83, 0xa5, 0x7c, 0x12, 0xa5, 0x05, 0xdb, 0x90,
	0xbd, 0x2f, 0x14, 0xd3, 0x71, 0x72, 0x96, 0xa8,
	0x8a, 0x7d, 0x84, 0x56, 0x71, 0x8d, 0x6a, 0x22,
	0x98, 0xab, 0x9e, 0x3d, 0xc3, 0x55, 0xef, 0xcc,
	0xa5, 0xc3, 0xdd, 0x5b, 0x8e, 0xbf, 0x03, 0x81,
	0x21, 0x40, 0xd6, 0x26, 0x91, 0x02, 0x45, 0x4e,
	0x20, 0x91, 0xcf, 0x8c, 0x51, 0x22, 0x02, 0x70,
	0xba, 0x05, 0x6b, 0x83, 0xef, 0x3f, 0x8e, 0x09,
	0xef, 0x88, 0xf5, 0x37, 0x1b, 0x89, 0x8d, 0xff,
	0x1e, 0xee, 0xe8, 0xb0, 0xac, 0xf2, 0x6e, 0xd4,
	0x3e, 0x25, 0xaf, 0xa0, 0x6d, 0x2e, 0xc0, 0x7f,
	0xb5, 0xa0, 0xcb, 0x90, 0x1f, 0x08, 0x1a, 0xe2,
	0x90, 0x20, 0x19, 0x71, 0x0c, 0xe8, 0x3f, 0xe5,
	0x39, 0xeb, 0x9a, 0x62, 0x4f, 0x06, 0xda, 0x3c,
	0x32, 0x59, 0xcc, 0x83, 0xe3, 0x83, 0x0f, 0x38,
	0x7d, 0x43, 0x37, 0x6c, 0x0b, 0x05, 0x65, 0x98,
	0x25, 0xdb, 0xf2, 0xc0, 0x2d, 0x39, 0x36, 0x5d,
	0xd4, 0xb6, 0xc2, 0x79, 0x73, 0x3e, 0xc2, 0x6e,
	0x54, 0xec, 0x78, 0x2b, 0x5d, 0xf1, 0xd1, 0xb4,
	0xb3, 0xcd, 0xf3, 0x89, 0xf5, 0x80, 0x79, 0x46,
	0xc0, 0x00, 0x00, 0x00, 0xc4, 0xf5, 0x1d, 0x08,
	0xf0, 0x34, 0x3a, 0x59, 0x00, 0x01, 0xcf, 0x01,
	0xdd, 0x01, 0x00, 0x00, 0x7f, 0x5a, 0x77, 0xcb,
	0xb1, 0xc4, 0x67, 0xfb, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x04, 0x59, 0x5a,
	0xfd, 0x37, 0x7a, 0x58, 0x5a, 0x00, 0x00, 0x04,
	0xe6, 0xd6, 0xb4, 0x46, 0x02, 0x00, 0x21, 0x01,
	0x16, 0x00, 0x00, 0x00, 0x74, 0x2f, 0xe5, 0xa3,
	0xe0, 0x00, 0xe0, 0x00, 0xb7, 0x5d, 0x00, 0x31,
	0x9b, 0xca, 0x19, 0xc5, 0x54, 0xec, 0xb6, 0x54,
	0xe7, 0xb1, 0x7d, 0xc4, 0x57, 0x9e, 0x6c, 0x89,
	0xad, 0x4a, 0x6d, 0x16, 0xd8, 0x3c, 0x05, 0x94,
	0x10, 0x16, 0x99, 0x38, 0x21, 0xa3, 0xb9, 0xc5,
	0x80, 0xff, 0xfc, 0xee, 0xd4, 0xd5, 0x3f, 0xdd,
	0x8c, 0xd7, 0x3d, 0x8f, 0x76, 0xec, 0x96, 0x9d,
	0x20, 0xac, 0xcb, 0x18, 0xf5, 0xb2, 0x9c, 0x12,
	0xf6, 0x7c, 0x33, 0xdc, 0x4f, 0x9a, 0xe5, 0x2d,
	0x63, 0x68, 0xa4, 0x2b, 0x1d, 0x0a, 0x1e, 0xf0,
	0xfe, 0x73, 0xf2, 0x5f, 0x7b, 0xb4, 0xea, 0x54,
	0xad, 0x27, 0xd1, 0xff, 0xb6, 0x50, 0x06, 0x7b,
	0x51, 0x3f, 0x25, 0x8a, 0xcf, 0x4c, 0x03, 0x3e,
	0xc3, 0xad, 0x47, 0x34, 0xcf, 0xba, 0x45, 0x79,
	0xd0, 0x7b, 0xf6, 0x66, 0x63, 0xc0, 0xc6, 0x69,
	0xa7, 0x51, 0x84, 0xa8, 0xa0, 0x0b, 0xbc, 0x6f,
	0x13, 0x89, 0xd6, 0x5e, 0xac, 0xca, 0x2f, 0xd2,
	0xe7, 0xe1, 0x1e, 0x78, 0x22, 0x3a, 0x59, 0x6c,
	0x9c, 0x8c, 0x65, 0xf1, 0x5b, 0xf4, 0xbf, 0xd5,
	0xdc, 0x05, 0xeb, 0x70, 0x10, 0xb8, 0x6c, 0xf2,
	0x13, 0x20, 0xb0, 0xdd, 0x3e, 0xb2, 0x92, 0x5b,
	0xa3, 0xf7, 0x94, 0xa1, 0xa1, 0x74, 0x36, 0x9a,
	0xf1, 0xd8, 0xc2, 0xf0, 0xc6, 0x29, 0x7e, 0x85,
	0x28, 0xf5, 0xf2, 0x21, 0x00, 0x00, 0x00, 0x00,
	0xc8, 0x80, 0x67, 0x40, 0xc3, 0xaa, 0x17, 0x57,
	0x00, 0x01, 0xd3, 0x01, 0xe1, 0x01, 0x00, 0x00,
	0x86, 0xdf, 0x9e, 0x05, 0xb1, 0xc4, 0x67, 0xfb,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x04, 0x59, 0x5a
#elif defined(DO_BZIP2)
	0x42, 0x5a, 0x68, 0x39, 0x31, 0x41, 0x59, 0x26,
	0x53, 0x59, 0x5d, 0x09, 0x24, 0x1d, 0x00, 0x00,
	0x13, 0xd7, 0x80, 0x00, 0x10, 0x40, 0x05, 0x00,
	0x04, 0x02, 0x00, 0x3e, 0xa7, 0xff, 0x40, 0x30,
	0x00, 0xac, 0x43, 0x54, 0xf5, 0x36, 0x4c, 0xa7,
	0xa8, 0xd3, 0x6a, 0x60, 0x81, 0x40, 0x00, 0xd0,
	0x32, 0x64, 0x0d, 0x53, 0xda, 0x02, 0x09, 0xa2,
	0x68, 0x34, 0xd1, 0x27, 0x4a, 0xdd, 0xf2, 0x0a,
	0x73, 0x43, 0xf9, 0xa2, 0x51, 0x85, 0x76, 0x45,
	0x9a, 0x68, 0x3a, 0xe7, 0x0d, 0xc0, 0x21, 0x4a,
	0xc4, 0xf9, 0xf7, 0x40, 0xc3, 0x10, 0xb2, 0x9b,
	0x58, 0x56, 0x71, 0x50, 0x2f, 0xa4, 0xc5, 0x61,
	0x19, 0xf6, 0x59, 0x06, 0x82, 0x03, 0x7f, 0xeb,
	0xd2, 0x61, 0x88, 0xcd, 0xe8, 0xf7, 0xe8, 0x87,
	0x59, 0x9d, 0xe1, 0xf8, 0x19, 0x6e, 0xad, 0x77,
	0xbf, 0x34, 0x17, 0x21, 0x6b, 0x91, 0xc9, 0x52,
	0xd0, 0x81, 0x1e, 0xb5, 0x0b, 0xee, 0x42, 0x84,
	0x80, 0xd5, 0xa1, 0x8a, 0x04, 0x18, 0x4d, 0xf3,
	0xda, 0x7e, 0x3c, 0x40, 0xa4, 0xdb, 0xe5, 0xf0,
	0x37, 0x40, 0x3a, 0x7d, 0xa7, 0x45, 0x21, 0xf2,
	0x5a, 0x7b, 0x59, 0x56, 0x16, 0xd5, 0xac, 0x9f,
	0x60, 0x85, 0x0e, 0xf5, 0x73, 0xd9, 0x47, 0xe2,
	0xee, 0x48, 0xa7, 0x0a, 0x12, 0x0b, 0xa1, 0x24,
	0x83, 0xa0,
	0x42, 0x5a, 0x68, 0x39, 0x31, 0x41, 0x59, 0x26,
	0x53, 0x59, 0x2c, 0x24, 0x39, 0xa0, 0x00, 0x00,
	0x1f, 0x55, 0x80, 0x00, 0x10, 0x40, 0x05, 0x06,
	0x00, 0x3f, 0xe7, 0xff, 0x40, 0x30, 0x00, 0xb5,
	0x91, 0x13, 0x4f, 0x54, 0x7a, 0x6a, 0x6d, 0x4d,
	0xa2, 0x68, 0x0c, 0x84, 0x53, 0xf5, 0x30, 0x89,
	0xa3, 0xd4, 0x0d, 0x0f, 0x49, 0xa0, 0xd4, 0xf4,
	0xd1, 0x53, 0xf4, 0x93, 0x69, 0x3c, 0x81, 0x1a,
	0x65, 0x53, 0x90, 0x51, 0x07, 0x2a, 0xad, 0x8f,
	0x63, 0xba, 0x25, 0xc2, 0x0c, 0x8b, 0xb9, 0x95,
	0x15, 0xd8, 0xda, 0x61, 0x5c, 0xa9, 0xe4, 0x0b,
	0x21, 0xc9, 0x97, 0x57, 0x01, 0x28, 0x9b, 0xfb,
	0x94, 0xb9, 0x48, 0xa3, 0x0a, 0xc6, 0x1c, 0x54,
	0x98, 0x9a, 0x39, 0xc3, 0x87, 0x90, 0x33, 0x58,
	0x2d, 0x3e, 0x16, 0xb1, 0xae, 0x26, 0x89, 0x75,
	0xf5, 0x77, 0xa5, 0x8e, 0x5b, 0x8c, 0x8a, 0x39,
	0xbd, 0x75, 0x21, 0x9d, 0x99, 0x18, 0x4a, 0x91,
	0xab, 0xbc, 0x08, 0x87, 0xa4, 0xf1, 0x81, 0xb5,
	0xb4, 0xb0, 0xfe, 0x6b, 0x9f, 0xbe, 0x19, 0x82,
	0xd1, 0x50, 0xe1, 0x5e, 0x13, 0xb5, 0xc6, 0x2c,
	0xa4, 0x82, 0xf2, 0x5c, 0xc3, 0x20, 0x41, 0x13,
	0x56, 0x63, 0x3d, 0xec, 0x71, 0x2a, 0xbf, 0x2c,
	0x60, 0x2f, 0x7a, 0x4d, 0xcb, 0x3f, 0x8b, 0xb9,
	0x22, 0x9c, 0x28, 0x48, 0x16, 0x12, 0x1c, 0xd0,
	0x00,
#elif defined(DO_ZSTD)
	0x28, 0xb5, 0x2f, 0xfd, 0x04, 0x58, 0x75, 0x04,
	0x00, 0xb2, 0x4c, 0x20, 0x17, 0xa0, 0x25, 0x69,
	0x03, 0xf0, 0xb2, 0x37, 0xb1, 0x5e, 0xb9, 0x24,
	0x56, 0x5b, 0x52, 0x22, 0x39, 0x01, 0x44, 0x2b,
	0x03, 0x55, 0xe3, 0x47,	0x03, 0x12, 0x9a, 0xe1,
	0xf0, 0x94, 0x0b, 0xe5, 0xe2, 0xba, 0x7e, 0xfe,
	0x9c, 0xc7, 0x61, 0x43, 0xc8, 0xfa, 0xf0, 0x3a,
	0xfa, 0x51, 0xaa, 0x50,	0xa6, 0x2d, 0x9a, 0x78,
	0xce, 0x2f, 0x61, 0x20, 0x6c, 0x7e, 0x35, 0x60,
	0xfb, 0xdd, 0x4c, 0x63, 0xfb, 0x95, 0x35, 0xc0,
	0x82, 0x59, 0xc2, 0xc9,	0x78, 0x6e, 0x30, 0xe6,
	0xd2, 0x72, 0x15, 0x14, 0x18, 0x62, 0x5d, 0xeb,
	0x2d, 0x9d, 0x3e, 0xee, 0x2e, 0x58, 0x58, 0xe9,
	0x40, 0x68, 0xb9, 0x2f,	0x23, 0x99, 0x2a, 0x4d,
	0xe8, 0x49, 0x79, 0x70, 0x1f, 0xf9, 0xe2, 0x34,
	0x2e, 0xab, 0xa5, 0xa3, 0xf2, 0x70, 0x98, 0xd0,
	0xb2, 0xb1, 0x3e, 0x5d,	0x90, 0x20, 0xd9, 0x36,
	0x8b, 0xdb, 0xaa, 0x20, 0x40, 0x03, 0x14, 0x06,
	0x03, 0x16, 0x2a, 0x9d, 0x31, 0xbd, 0x28, 0x3b,
	0x0c, 0xac, 0x41,
	0x28, 0xb5, 0x2f, 0xfd, 0x04, 0x58, 0xbd, 0x04,
	0x00, 0x62, 0xcd, 0x22, 0x19, 0xa0, 0x25, 0x69,
	0x03, 0x60, 0x72, 0xc9, 0x36, 0xda, 0xd2, 0x8b,
	0xfc, 0xbf, 0x25, 0x42, 0xa9, 0x82, 0x38, 0x70,
	0x1a, 0x2e, 0x54, 0x95,	0x33, 0x02, 0x03, 0x51,
	0x36, 0x51, 0x80, 0xcc, 0x7a, 0x6e, 0x52, 0x2e,
	0x75, 0x64, 0x2d, 0x33, 0x2c, 0xd6, 0xdb, 0xfc,
	0x39, 0x31, 0xd5, 0xa8,	0xa2, 0x40, 0xd7, 0x12,
	0x4c, 0xc6, 0x76, 0xdc, 0x1e, 0x0f, 0xf4, 0x4e,
	0x0a, 0xd3, 0x0c, 0x87, 0x67, 0x25, 0x25, 0x52,
	0x66, 0x87, 0x95, 0xc6,	0x69, 0x0c, 0xb4, 0x5e,
	0x1d, 0xe7, 0x5e, 0xcd, 0x47, 0x41, 0x80, 0x89,
	0x5c, 0xa5, 0x4a, 0x32, 0x26, 0xb3, 0x3d, 0x2b,
	0xd5, 0xc0, 0x16, 0xde,	0xfb, 0x65, 0xcd, 0x6a,
	0x0c, 0x3f, 0xe7, 0xd6, 0xb2, 0x17, 0x7c, 0x25,
	0x35, 0x6b, 0x58, 0xf0, 0x95, 0xb5, 0xf2, 0xe4,
	0x4e, 0xf0, 0x34, 0x4f,	0x5f, 0x39, 0xd1, 0x90,
	0xf8, 0xb9, 0x59, 0xbe, 0x2e, 0xf9, 0xd4, 0x02,
	0x98, 0x50, 0x5a, 0xc2, 0xcf, 0xe1, 0x08, 0x02,
	0x00, 0x0f, 0x1e, 0x44,	0x40, 0x79, 0x50, 0x67,
	0x3d, 0xd3, 0x35, 0x8f,
#elif defined(DO_GZIP)
	0,
#endif
};

static const char orig[] =
"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod\n"
"tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,\n"
"quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo\n"
"consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse\n"
"cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non\n"
"proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\n";

#if defined(DO_XZ)
#define mkdecompressor decompressor_stream_xz_create
#define mkcompressor compressor_stream_xz_create
#elif defined(DO_BZIP2)
#define mkdecompressor decompressor_stream_bzip2_create
#define mkcompressor compressor_stream_bzip2_create
#elif defined(DO_ZSTD)
#define mkdecompressor decompressor_stream_zstd_create
#define mkcompressor compressor_stream_zstd_create
#elif defined(DO_GZIP)
#define mkdecompressor decompressor_stream_gzip_create
#define mkcompressor compressor_stream_gzip_create
#endif

/*****************************************************************************/

static size_t mo_written = 0;
static sqfs_u8 mo_buffer[1024];
static bool mo_flushed = false;

static int mem_append(ostream_t *strm, const void *data, size_t size);
static int mem_flush(ostream_t *strm);

static ostream_t mem_ostream = {
	{ 1, NULL, NULL, },
	mem_append,
	NULL,
	mem_flush,
	NULL,
};

static int mem_append(ostream_t *strm, const void *data, size_t size)
{
	TEST_ASSERT(strm == &mem_ostream);
	TEST_NOT_NULL(data);
	TEST_ASSERT(size > 0);

	TEST_ASSERT(mo_written <= sizeof(mo_buffer));
	TEST_ASSERT(size <= (sizeof(mo_buffer) - mo_written));

	memcpy(mo_buffer + mo_written, data, size);
	mo_written += size;

	return 0;
}

static int mem_flush(ostream_t *strm)
{
	TEST_ASSERT(strm == &mem_ostream);
	TEST_ASSERT(!mo_flushed);
	mo_flushed = true;
	return 0;
}

/*****************************************************************************/

static void run_unpack_test(const void *blob, size_t size)
{
	istream_t *istream, *mem_istream;
	xfrm_stream_t *xfrm;
	sqfs_s32 ret;
	size_t i;
	char c;

	mem_istream = istream_memory_create("memstream", 7, blob, size);
	TEST_NOT_NULL(mem_istream);

	xfrm = mkdecompressor();
	TEST_NOT_NULL(xfrm);
	TEST_EQUAL_UI(((sqfs_object_t *)xfrm)->refcount, 1);
	TEST_EQUAL_UI(((sqfs_object_t *)mem_istream)->refcount, 1);

	istream = istream_xfrm_create(mem_istream, xfrm);

	TEST_NOT_NULL(istream);
	TEST_EQUAL_UI(((sqfs_object_t *)istream)->refcount, 1);
	TEST_EQUAL_UI(((sqfs_object_t *)xfrm)->refcount, 2);
	TEST_EQUAL_UI(((sqfs_object_t *)mem_istream)->refcount, 2);

	for (i = 0; i < (sizeof(orig) - 1); ++i) {
		ret = istream_read(istream, &c, 1);
		TEST_EQUAL_I(ret, 1);
		TEST_EQUAL_I(c, orig[i]);
	}

	ret = istream_read(istream, &c, 1);
	TEST_EQUAL_I(ret, 0);

	ret = istream_read(istream, &c, 1);
	TEST_EQUAL_I(ret, 0);

	TEST_EQUAL_UI(mem_istream->buffer_used, 0);
	TEST_EQUAL_UI(mem_istream->buffer_offset, 0);
	TEST_ASSERT(mem_istream->eof);

	sqfs_drop(istream);
	TEST_EQUAL_UI(((sqfs_object_t *)mem_istream)->refcount, 1);
	TEST_EQUAL_UI(((sqfs_object_t *)xfrm)->refcount, 1);
	sqfs_drop(xfrm);
	sqfs_drop(mem_istream);
}

static void run_pack_test(void)
{
	xfrm_stream_t *xfrm;
	ostream_t *ostream;
	size_t i;
	int ret;

	mo_written = 0;
	mo_flushed = false;

	xfrm = mkcompressor(NULL);
	TEST_NOT_NULL(xfrm);
	TEST_EQUAL_UI(((sqfs_object_t *)xfrm)->refcount, 1);
	TEST_EQUAL_UI(((sqfs_object_t *)&mem_ostream)->refcount, 1);

	ostream = ostream_xfrm_create(&mem_ostream, xfrm);

	TEST_NOT_NULL(ostream);
	TEST_EQUAL_UI(((sqfs_object_t *)ostream)->refcount, 1);
	TEST_EQUAL_UI(((sqfs_object_t *)xfrm)->refcount, 2);
	TEST_EQUAL_UI(((sqfs_object_t *)&mem_ostream)->refcount, 2);

	for (i = 0; i < (sizeof(orig) - 1); ++i) {
		ret = ostream_append(ostream, orig + i, 1);
		TEST_EQUAL_I(ret, 0);
	}

	ret = ostream_flush(ostream);
	TEST_EQUAL_I(ret, 0);

	TEST_ASSERT(mo_flushed);
	TEST_ASSERT(mo_written < sizeof(orig));
	ret = memcmp(mo_buffer, orig, mo_written);
	TEST_ASSERT(ret != 0);

	sqfs_drop(ostream);
	TEST_EQUAL_UI(((sqfs_object_t *)&mem_ostream)->refcount, 1);
	TEST_EQUAL_UI(((sqfs_object_t *)xfrm)->refcount, 1);
	sqfs_drop(xfrm);
}

int main(int argc, char **argv)
{
	(void)argc; (void)argv;

	/* normal stream */
	run_unpack_test(blob_in, sizeof(blob_in));

	/* concatenated streams */
#if !defined(DO_GZIP)
	run_unpack_test(blob_in_concat, sizeof(blob_in_concat));
#else
	(void)blob_in_concat;
#endif
	/* compress */
	run_pack_test();

	/* restore from compressed */
	run_unpack_test(mo_buffer, mo_written);
	return EXIT_SUCCESS;
}
