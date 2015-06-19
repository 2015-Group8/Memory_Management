/*
 * libslp-db-util
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Hakjoo Ko <hakjoo.ko@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __DB_UTIL_FUNC_H__
#define __DB_UTIL_FUNC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sqlite3.h>

#ifndef EXPORT_API
#define EXPORT_API __attribute__ ((visibility("default")))
#endif

#ifndef PARAM_IN
#define PARAM_IN
#endif

#ifndef PARAM_OUT
#define PARAM_OUT
#endif

typedef enum {
	DB_UTIL_ERROR = SQLITE_ERROR,
	DB_UTIL_OK = SQLITE_OK,
} db_util_err;


#ifdef __cplusplus
}
#endif
#endif	/* __DB_UTIL_FUNC_H__ */
