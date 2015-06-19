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

#ifndef __UTIL_FUNC_H__
#define __UTIL_FUNC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <db-util-common.h>

#define DB_UTIL_REGISTER_HOOK_METHOD    0x00000001
#define DB_UTIL_LUCENE_INDEX            0x00000002

/**
* @defgroup StorageFW Storage Framework
* In order to support applications using DB
*/

/**
 * @defgroup DB_UTIL
 * @ingroup StorageFW
 * @{
 */



/**
 * @brief invoke sqlite3_open with platform common configuration
 * @details register busy handler, create localized collation
 * @param [in] database file name (UTF-8)
 * @param [out] SQLite database handle
 * @param [in] option value
 * @return sqlite3 function return value will be returned
 * @see	db_util_open_with_options()
 * @see	db_util_close()
 *
 */
EXPORT_API int db_util_open(const char *pszFilePath, sqlite3 **ppDB,
						int nOption);

/**
 * @brief invoke sqlite3_open_v2 with platform common configuration
 * @details register busy handler, create localized collation
 * @param [in] database file name (UTF-8)
 * @param [out] SQLite database handle
 * @param [in] sqlite3_open_v2 flags
 * @param [in] Name of VFS module to use
 * @return sqlite3 function return value will be returned
 * @see	db_util_open()
 * @see	db_util_close()
 *
 */
EXPORT_API int db_util_open_with_options(const char *pszFilePath,
						sqlite3 **ppDB, int flags,
						const char *zVfs);

/**
 * @brief closing a database connection
 * @param [in] SQLite database handle
 * @return sqlite3_close function return value will be returned
 * @see	db_util_open()
 * @see	db_util_open_with_options()
 *
 */
EXPORT_API int db_util_close(sqlite3 *ppDB);

/**
*@}
*/

#ifdef __cplusplus
}
#endif
#endif	/* __UTIL_FUNC_H__ */
