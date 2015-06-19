/*
 *  RUA
 *
 * Copyright (c) 2000 - 2012 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Jayoun Lee <airjany@samsung.com>
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

/**
 * @file 	rua.h
 * @brief       RUA API declaration header file.
 * @author      Jinwoo Nam (jwoo.nam@samsung.com)
 * @version     0.1
 * @history     0.1: RUA API Declarations, structure declaration
 */

#ifndef __RUA_H__
#define __RUA_H__

#include <sqlite3.h>
#include <time.h>

#ifndef API
#define API __attribute__ ((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup RUA rua
 * @{
 */

/**
 * @}
 */

/**
 * @addtogroup RUA
 * @{
 */

/**
 * @struct rua_rec
 * @brief RUA record info structure
 */
struct rua_rec {
	int id;		/**<  primary key */
	char *pkg_name;		/**< package name */
	char *app_path;		/**< application path */
	char *arg;		/**< application launching argument */
	time_t launch_time;		/**< application launching time */
};

/**
 * @brief	Clear history
 * @return 	0 on success, otherwise a nagative error value
 * @retval	0 on successful
 * @retval	-1 on failed
 */
API int rua_clear_history(void);

/**
 * @brief	Delete history with pkg_name
 * @param[in]	pkg_name package name to delete history
 * @return	0 on success, otherwise a nagative error value
 * @retval	0 on successful
 * @retval	-1 on failed
 */
API int rua_delete_history_with_pkgname(char *pkg_name);

/**
 * @brief	Delete history with app_path
 * @param[in]	app_path package name to delete history
 * @return	0 on success, otherwise a nagative error value
 * @retval	0 on successful
 * @retval	-1 on failed
 */
API int rua_delete_history_with_apppath(char *app_path);

/**
 * @brief	Add application to recently used application list
 * @param[in]	rec  record to add history
 * @return	0 on success, otherwise a nagative error value
 * @retval	0 on successful
 * @retval	-1 on failed
 */
API int rua_add_history(struct rua_rec *rec);

/**
 * @brief	Load recently used application history db.
 * @param[out]	table db table pointer
 * @param[out]	nrows the number of record
 * @param[out]	ncols the number of field
 * @return	0 on success, otherwise a nagative error value
 * @retval	0 on successful
 * @retval	-1 on failed
 */
API int rua_history_load_db(char ***table, int *nrows, int *ncols);

/**
 * @brief	Unload recently used application history db.
 * @param[in]	table db table pointer to unload
 * @return	0 on success, otherwise a nagative error value
 * @retval	0 on successful
 * @retval	-1 on failed
 */
API int rua_history_unload_db(char ***table);

/**
 * @brief	Load recently used application record.
 * @param[out]	rec record to load
 * @param[in]	table db table pointer
 * @param[in]	nrows the number of record
 * @param[in]	ncols the number of field
 * @param[in]	row record index to load
 * @return	0 on success, otherwise a nagative error value
 * @retval	0 on successful
 * @retval	-1 on failed
 */
API int rua_history_get_rec(struct rua_rec *rec, char **table,
				int nrows, int ncols, int row);

/**
 * @brief	Check some package is latest or not with package name
 * @param[in]	pkg_name package name
 * @return	0 on success, otherwise a nagative error value
 * @retval	0 if given pkg_name is lastest application
 * @retval	-1 if not lastest applicaton or on failed
 */
API int rua_is_latest_app(const char *pkg_name);

/**
 * @brief	Initialize rua
 * @return	0 on success, otherwise a nagative error value
 * @retval	0 on successful
 * @retval	-1 on failed
 */
API int rua_init(void);

/**
 * @brief	Finalize rua
 * @return	0 on success, otherwise a nagative error value
 * @retval	0 on successful
 * @retval	-1 on failed
 */
API int rua_fini(void);

#ifdef __cplusplus
}
#endif
#endif				/*__RUA_H__*/
