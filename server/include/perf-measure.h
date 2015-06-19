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

#ifndef __PERF_MEASURE__
#define __PERF_MEASURE__

#include <time.h>


//#define PERF_MEASURE_ENABLE

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PERF_MEASURE_ENABLE

unsigned int _perf_measure_start(const char *tag, char *func_name, int line);
unsigned int _perf_measure_end(const char *tag, unsigned int ts_start,
			char *func_name, int line);

#define PERF_MEASURE_START(tag) _perf_measure_start(tag, __func__,__LINE__)
#define PERF_MEASURE_END(tag, ts_start) \
	_perf_measure_end(tag, ts_start,__func__, __LINE__)

#else

#define PERF_MEASURE_START(tag) (0)
#define PERF_MEASURE_END(tag, ts_start) (0)

#endif













#ifdef __cplusplus
}
#endif
#endif				/*__PERF_MEASURE__*/
