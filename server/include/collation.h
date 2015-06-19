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

#ifndef __DBUTIL_COLLATION_H__
#define __DBUTIL_COLLATION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <db-util-common.h>

/*
 * Collations Types
 *
 * These types are intended for use in the
 * 2nd parameter to the [db_util_create_collation()] interface.
 * The meanings of the various types is shown below.
 *
 * [DB_UTIL_COL_UCA]
 * Unicode Collation Algorithm / Locale InSensitive / Accent Sensitive / Case Insensitive
 * This type will be mostly used in 'ORDER BY' clause of sql for sorted list.
 *
 * [DB_UTIL_COL_LS_AS_CI]
 * Locale Sensitive / Accent Sensitive / Case Insensitive
 * This type will be mostly used in 'ORDER BY' clause of sql for sorted list.
 *
 * [DB_UTIL_COL_LS_AI_CI]
 * Locale Sensitive / Accent Insensitive / Case Insensitive
 * This type will be mostly used for '=' operator comparison in 'WHERE' clause.

 * [DB_UTIL_COL_LS_AI_CI_LC]
 * Locale Sensitive / Accent Insensitive / Loop Comparison
 * This type will be mostly used for 'LIKE' operator comparison in 'WHERE' clause.
 *
 * [DB_UTIL_COL_KR_IC]
 * Locale Sensitive / Korea / Initial(leading) Consonant
 * Compares string data using initial(leading) consonant for korea locale.
 * This type will be mostly used for '=' operator comparison in 'WHERE' clause.
 *
 * [DB_UTIL_COL_KR_IC_LC]
 * Locale Sensitive / Korea / Initial(leading) Consonant / Loop Comparison
 * Compares string data using initial(leading) consonant for korea locale.
 * This type will be mostly used for 'LIKE' operator comparison in 'WHERE' clause.
 */

typedef enum {
	DB_UTIL_COL_UCA,
	DB_UTIL_COL_LS_AS_CI,
	DB_UTIL_COL_LS_AI_CI,
	DB_UTIL_COL_LS_AI_CI_LC,
	DB_UTIL_COL_KO_IC,
	DB_UTIL_COL_KO_IC_LC
} db_util_collate_type;

/*
 * Text Encodings
 *
 * These encodings are intended for use in the
 * 3rd parameter to the [db_util_create_collation()] interface.
 */
typedef enum {
	DB_UTIL_COL_UTF8 = SQLITE_UTF8,
	DB_UTIL_COL_UTF16 = SQLITE_UTF16
} db_util_collate_textrep;


/**
 * @defgroup DB_UTIL
 * @ingroup StorageFW
 * @{
 */

/**
 * @fn int  db_util_create_collation(sqlite3 *db_handle, db_util_collate_type type, db_util_collate_textrep text_type, char* col_name);
 * This function defines a new collating sequences with the database connection specified as the firtst argument.
 * This function is needed to be invoked after [db_util_open()].
 *
 * @param[in] Db connection handle to create collation with
 * @param[in] Collation type. This value must be one of the [db_util_collate_type]
 * @param[in] Encoding of text passed to the collating function callback
 * @param[in] The name of collation(UTF-8 string)
 * return     This function returns DB_UTIL_OK or error code on failure
 * @exception None
 * @remarks   None
 * @pre       Database connected
 * @post      None
 * @code
 */
EXPORT_API int db_util_create_collation(
	PARAM_IN sqlite3 *db_handle,
	PARAM_IN db_util_collate_type type,
	PARAM_IN db_util_collate_textrep text_type,
	PARAM_IN char* col_name
);

/**
*@}
*/

#ifdef __cplusplus
}
#endif
#endif	/*	__DBUTIL_COLLATION_H__	*/
