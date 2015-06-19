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

#ifndef __RUA_SCHEMA_H__
#define __RUA_SCHEMA_H__

#define CREATE_RUA_HISTORY_TABLE " \
create table if not exists rua_history ( \
id INTEGER PRIMARY KEY, \
pkg_name TEXT, \
app_path TEXT, \
arg TEXT, \
launch_time INTEGER \
);"

/* table index */
enum {
	RUA_COL_ID = 0x00,
	RUA_COL_PKGNAME,
	RUA_COL_APPPATH,
	RUA_COL_ARG,
	RUA_COL_LAUNCHTIME
};
#endif				/* __RUA_SCHEMA_H__ */
