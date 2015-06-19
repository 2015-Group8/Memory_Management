/*
 * ail
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Jayoun Lee <airjany@samsung.com>, Sewook Park <sewook7.park@samsung.com>, Jaeho Lee <jaeho81.lee@samsung.com>
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




#ifndef __AIL_H__
#define __AIL_H__

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/**
 * @open
 * @ingroup APPLICATION_FRAMEWORK
 * @defgroup ail Application Information Library
 */

/**
 * @file       ail.h
 * @brief      Application Information Library header
 * @author     Sunghyuk Lee (sunghyuk.lee@samsung.com), Jin Yoon (jinny.yoon@samsung.com)
 * @date       2011-07-30
 * @version    0.1
 */

/**
 * @addtogroup ail
 * @{
 */

/**
 * @brief string type properties
 */
#define	AIL_PROP_PACKAGE_STR			"AIL_PROP_PACKAGE_STR"
#define	AIL_PROP_EXEC_STR			"AIL_PROP_EXEC_STR"
#define	AIL_PROP_NAME_STR			"AIL_PROP_NAME_STR"
#define	AIL_PROP_TYPE_STR			"AIL_PROP_TYPE_STR"
#define	AIL_PROP_ICON_STR			"AIL_PROP_ICON_STR"
#define	AIL_PROP_CATEGORIES_STR			"AIL_PROP_CATEGORIES_STR"
#define	AIL_PROP_VERSION_STR			"AIL_PROP_VERSION_STR"
#define	AIL_PROP_MIMETYPE_STR			"AIL_PROP_MIMETYPE_STR"
#define	AIL_PROP_X_SLP_SERVICE_STR		"AIL_PROP_X_SLP_SERVICE_STR"
#define	AIL_PROP_X_SLP_PACKAGETYPE_STR		"AIL_PROP_X_SLP_PACKAGETYPE_STR"
#define	AIL_PROP_X_SLP_PACKAGECATEGORIES_STR	"AIL_PROP_X_SLP_PACKAGECATEGORIES_STR"
#define	AIL_PROP_X_SLP_PACKAGEID_STR		"AIL_PROP_X_SLP_PACKAGEID_STR"
#define	AIL_PROP_X_SLP_SVC_STR			"AIL_PROP_X_SLP_SVC_STR"
#define	AIL_PROP_X_SLP_EXE_PATH			"AIL_PROP_X_SLP_EXE_PATH"
#define	AIL_PROP_X_SLP_APPID_STR		"AIL_PROP_X_SLP_APPID_STR"


/**
 * @brief integer type properties
 */
#define	AIL_PROP_X_SLP_TEMP_INT			"AIL_PROP_X_SLP_TEMP_INT"
#define	AIL_PROP_X_SLP_INSTALLEDTIME_INT	"AIL_PROP_X_SLP_INSTALLEDTIME_INT"

/**
 * @brief boolean type properties
 */
#define	AIL_PROP_NODISPLAY_BOOL			"AIL_PROP_NODISPLAY_BOOL"
#define	AIL_PROP_X_SLP_TASKMANAGE_BOOL		"AIL_PROP_X_SLP_TASKMANAGE_BOOL"
#define	AIL_PROP_X_SLP_MULTIPLE_BOOL		"AIL_PROP_X_SLP_MULTIPLE_BOOL"
#define	AIL_PROP_X_SLP_REMOVABLE_BOOL		"AIL_PROP_X_SLP_REMOVABLE_BOOL"
#define	AIL_PROP_X_SLP_INACTIVATED_BOOL		"AIL_PROP_X_SLP_INACTIVATED_BOOL"


/**
 * @brief A handle for filters
 */
typedef struct ail_filter *ail_filter_h;

/**
 * @brief A handle for appinfos
 */
typedef struct ail_appinfo *ail_appinfo_h;

/**
 * @brief return values 
 */
typedef enum {
	AIL_ERROR_OK = 0,						/**< General success */
	AIL_ERROR_FAIL = -1,					/**< General error */
	AIL_ERROR_DB_FAILED = -2,				/**< Database error */
	AIL_ERROR_OUT_OF_MEMORY = -3,			/**< Out of memory */
	AIL_ERROR_INVALID_PARAMETER = -4,		/**< Invalid parameter */
	AIL_ERROR_NO_DATA = -5,					/**< Success, but no data */
} ail_error_e;

/**
 * @fn ail_error_e ail_filter_new(ail_filter_h *filter)
 *
 * @brief  Create a new filter handle which is used to filter records from Application Information Database. You can add filtering conditions to filter with ail_filter_add_xxx functions. All conditions are ANDed.
 *
 * @par Sync (or) Async : Synchronous API.
 *
 * @param[out] filter a pointer to a filter which is newly created
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 * @retval	AIL_ERROR_OUT_OF_MEMORY			out of memory
 *
 * @pre None
 * @post If the filter is no longer used, it should be freed with ail_filter_destroy()
 *
 * @see  ail_filter_destroy()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
int count_packages()
{
	ail_filter_h filter;
	ail_error_e ret;
	int n;

	ret = ail_filter_new(&filter);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_add_bool(filter, AIL_PROP_NODISPLAY_BOOL, false);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_add_str(filter, AIL_PROP_MIMETYPE_STR, "audio/wav");
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_count_appinfo(filter, &n);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}
	ret = ail_filter_destroy(filter);

	printf("N of packages not to be displayed and supporting 'audo/wav' mime type = %d\n", n);

	return n;
}
 * @endcode
 */
ail_error_e ail_filter_new(ail_filter_h *filter);



/**
 * @fn ail_error_e ail_error_e ail_filter_add_int(ail_filter_h filter, const char *property, const int value)
 *
 * @brief Add integer condition to filter
 *
 * @par Sync (or) Async : Synchronous API
 *
 * @param[in] filter	a filter handle which can be create with ail_filter_new()
 * @param[in] property		a property type of integer
 * @param[in] value		the value to filter by
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 * @retval	AIL_ERROR_OUT_OF_MEMORY			out of memory
 *
 * @pre The filter should be valid handle which was created by ail_filter_new()
 *
 * @see  ail_filter_new()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
int count_packages()
{
	ail_filter_h filter;
	ail_error_e ret;
	int n;

	ret = ail_filter_new(&filter);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_add_int(filter, AIL_PROP_X_SLP_BASELAYOUTWIDTH_INT, 480);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_count_appinfo(filter, &n);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	printf("N of packages = %d\n", n);

	return n;
}
 * @endcode
 */
ail_error_e ail_filter_add_int(ail_filter_h filter, const char *property, const int value);


/**
 * @fn ail_error_e ail_error_e ail_filter_add_bool(ail_filter_h filter, const char *property, const bool value)
 *
 * @brief Add boolean condition to filter by. The value can be true/false only
 *
 * @par Sync (or) Async : Synchronous API
 *
 * @param[in] filter	 a filter handle which can be create with ail_filter_new()
 * @param[in] property	 a property type of boolean
 * @param[in] value	 the value to filter by
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 * @retval	AIL_ERROR_OUT_OF_MEMORY			out of memory
 *
 * @pre The filter should be valid handle which was created by ail_filter_new()
 *
 * @see  ail_filter_new()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
int count_packages()
{
	ail_filter_h filter;
	ail_error_e ret;
	int n;

	ret = ail_filter_new(&filter);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_add_bool(filter, AIL_PROP_X_SLP_REMOVABLE_BOOL, true);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_count_appinfo(filter, &n);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	fprintf(stderr, "N of packages = %d\n", n);

	return n;
}
 * @endcode
 */
ail_error_e ail_filter_add_bool(ail_filter_h filter, const char *property, bool value);



/**
 * @fn ail_error_e ail_error_e ail_filter_add_str(ail_filter_h filter, const char *property, const char *value)
 *
 * @brief Add string condition to filter by. The string is case-sensitive.
 *
 * @par Sync (or) Async : Synchronous API
 *
 * @param[in] filter	 a filter handle which can be create with ail_filter_new()
 * @param[in] property	 a property type of string
 * @param[in] value	 the value to filter by
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 * @retval	AIL_ERROR_OUT_OF_MEMORY			out of memory
 *
 * @pre The filter should be valid handle which was created by ail_filter_new()
 *
 * @see  ail_filter_new()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
int count_packages()
{
	ail_filter_h filter;
	ail_error_e ret;
	int n;

	ret = ail_filter_new(&filter);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_add_str(filter, AIL_PROP_PACKAGE_STR, "org.tizen.memo");
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_count_appinfo(filter, &n);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	fprintf(stderr, "N of packages = %d\n", n);

	return n;
}
 * @endcode
 */
ail_error_e ail_filter_add_str(ail_filter_h filter, const char *property, const char *value);



/**
 * @fn ail_error_e ail_filter_destroy(ail_filter_h filter)
 *
 * @brief Destroy a filter which is not used any longer.
 *
 * @par Sync (or) Async : Synchronous API
 *
 * @param[in] filter	filter handle
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK	success
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 *
 * @post If the filter is no longer used, it should be freed with ail_filter_destroy()
 *
 * @see  ail_filter_new()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
int count_packages()
{
	ail_filter_h filter;
	ail_error_e ret;
	int n;

	ret = ail_filter_new(&filter);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_add_bool(filter, AIL_PROP_X_SLP_REMOVABLE_BOOL, true);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_count_appinfo(filter, &n);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	printf("N of removable packages = %d\n", n);

	ret = ail_filter_add_str(filter, AIL_PROP_MIMETYPE_STR, "audio/wav");
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_count_appinfo(filter, &n);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	printf("N of packages removable and supporting 'audo/wav' mime type = %d\n", n);

	ret = ail_filter_destroy(filter);

	return n;
}
 * @endcode
 */
ail_error_e ail_filter_destroy(ail_filter_h filter);



/**
 * @brief return value type of ail_list_appinfo_cb
 */
typedef enum {
	AIL_CB_RET_CONTINUE = 1,		/**< continue */
	AIL_CB_RET_CANCEL = 0,			/**< cancel */
} ail_cb_ret_e;

/**
 * @fn ail_cb_ret_e (*ail_list_appinfo_cb) (const ail_appinfo_h appinfo_h, void *user_data)
 *
 * @breif Specifies the type of functions passed to ail_filter_list_appinfo_foreach().
 *
 * @param[in] appinfo_h	the appinfo's handle
 * @param[in] user_data user data passed to ail_filtet_list_appinfo_foreach()
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_CB_RET_CONTINUE				return if you continue iteration
 * @retval	AIL_CB_RET_CANCEL				return if you cancel iteration
 *
 * @see  ail_filter_list_appinfo_foreach()
 */
typedef ail_cb_ret_e (*ail_list_appinfo_cb) (const ail_appinfo_h appinfo_h, void *user_data);

/**
 * @fn ail_error_e ail_error_e ail_filter_list_appinfo_foreach(ail_filter_h filter, ail_list_appinfo_cb func, void *user_data)
 *
 * @brief Calls the callback function for each package filtered by given filter. If the filter is not given (i.e filter handle is NULL), it is invoked for all packages.
 *
 * @par Sync (or) Async : Synchronous API
 *
 * @param[in] filter		a filter handle
 * @param[in] func			the function to call with each package's appinfo
 * @param[in] user_data		user_data to pass to the function
 *
 * @return  0 if success, negative value(<0) if fail\n
 * @retval AIL_ERROR_OK					success
 * @retval AIL_ERROR_DB_FAILED				database error
 * @retval AIL_ERROR_INVALID_PARAMETER		invalid parameter
 *
 * @see  ail_list_appinfo_cb
 * @see ail_filter_add_bool()
 * @see ail_filter_add_int()
 * @see ail_filter_add_str()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code

ail_cb_ret_e appinfo_func(const ail_appinfo_h appinfo, void *user_data)
{
	int *i = (int *)user_data;
	char *package;

	ail_appinfo_get_str(appinfo, AIL_PROP_PACKAGE_STR, &package);
	printf("i=%d %s\n", (*i)++, package);

	if (*i > 30)
		return AIL_CB_RET_CANCEL;

	return AIL_CB_RET_CONTINUE;
}

int list_packages()
{
	ail_filter_h filter;
	ail_error_e ret;
	int i=0;

	ret = ail_filter_new(&filter);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_add_bool(filter, AIL_PROP_X_SLP_REMOVABLE_BOOL, true);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_add_str(filter, AIL_PROP_TYPE_STR, "Application");
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	printf("List packages which are removable and 'Application' typed\n");
	ail_filter_list_appinfo_foreach(filter, appinfo_func, (void *)&i);

	ail_filter_destroy(filter);
	
	return 0;
}
 * @endcode
 */
ail_error_e ail_filter_list_appinfo_foreach(ail_filter_h filter,
                                            ail_list_appinfo_cb appinfo_func,
                                            void *user_data);



/**
 * @fn ail_error_e ail_error_e ail_filter_count_appinfo(ail_filter_h filter, int *count)
 *
 * @brief Gets the number of package which is filtered by the given filter. If the filter is not given (i.e filter handle is NULL), all package are counted.
 *
 * @par Sync (or) Async : Synchronous API
 *
 * @param[in] filter	a filter handle
 * @param[in] count		the number of appinfo which is filtered
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 * @retval 	AIL_ERROR_OUT_OF_MEMORY			out of memory
 *
 * @pre None
 * @post None
 *
 * @see ail_filter_new()
 * @see ail_filter_add_bool()
 * @see ail_filter_add_int()
 * @see ail_filter_add_str()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
int count_packages()
{
	ail_filter_h filter;
	ail_error_e ret;
	int n;

	ret = ail_filter_new(&filter);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_add_bool(filter, AIL_PROP_NODISPLAY_BOOL, true);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	ret = ail_filter_count_appinfo(filter, &n);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	printf("N of package not to be displayed = %d", n);

	ret = ail_filter_count_appinfo(NULL, &n);
	if (ret != AIL_ERROR_OK) {
		return -1;
	}

	printf("N of all package = %d\n", n);

	return n;
}
 * @endcode
 */
ail_error_e ail_filter_count_appinfo(ail_filter_h filter, int *count);



/**
 * @fn ail_error_e ail_package_get_appinfo(const char *package, ail_appinfo_h *handle)
 *
 * @brief get an application information related to a package. 
 	This API just retrieves all the information of the package from Application Information Database.
	All data related to the package are loaded in the memory after calling this function. 
	If you want to read a value from the retrieving data, you have to use the functions of ail_appinfo_get_xxx.

 * @par Sync (or) Async : Synchronous API.
 *
 * @param[in] package package name what you want to know about.
 * @param[out] handle handle will be used with the functions of ail_appinfo_get_xxx. If no data, it will be NULL.
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval 	AIL_ERROR_FAIL					internal error
 * @retval	AIL_ERROR_DB_FAILED				database error
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 * @retval	AIL_ERROR_NO_DATA				no data. cannot find the package.
 *
 * @pre declare a handle before calling this function. The handle is used as a second argument of this API.
 * @post destroy the handle with the function of ail_package_destroy_appinfo after using it all.
 *
 * @see  ail_package_destroy_appinfo(), ail_appinfo_get_bool(), ail_appinfo_get_int(), ail_appinfo_get_str()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
static ail_error_e _get_name(const char *package)
{
	ail_appinfo_h handle;
	ail_error_e ret;
	char *str;

	ret = ail_package_get_appinfo(package, &handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	ret = ail_appinfo_get_str(handle, AIL_PROP_NAME_STR, &str);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}
	fprintf(stderr, "Package[%s], Property[%s] : %s\n", package, property, str);

	ret = ail_package_destroy_appinfo(handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	return AIL_ERROR_OK;
}
 * @endcode
 */
ail_error_e ail_package_get_appinfo(const char *package, ail_appinfo_h *handle);


/**
 * @fn ail_error_e ail_get_appinfo(const char *appid, ail_appinfo_h *handle)
 *
 * @brief get an application information related to a appid.
	This API just retrieves all the information of the application from Application Information Database.
	All data related to the appid are loaded in the memory after calling this function.
	If you want to read a value from the retrieving data, you have to use the functions of ail_appinfo_get_xxx.

 * @par Sync (or) Async : Synchronous API.
 *
 * @param[in] appid appid what you want to know about.
 * @param[out] handle handle will be used with the functions of ail_appinfo_get_xxx. If no data, it will be NULL.
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval 	AIL_ERROR_FAIL					internal error
 * @retval	AIL_ERROR_DB_FAILED				database error
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 * @retval	AIL_ERROR_NO_DATA				no data. cannot find the package.
 *
 * @pre declare a handle before calling this function. The handle is used as a second argument of this API.
 * @post destroy the handle with the function of ail_get_appinfo after using it all.
 *
 * @see  ail_get_appinfo(), ail_appinfo_get_bool(), ail_appinfo_get_int(), ail_appinfo_get_str()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
static ail_error_e _get_name(const char *appid)
{
	ail_appinfo_h handle;
	ail_error_e ret;
	char *str;

	ret = ail_get_appinfo(appid, &handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	ret = ail_appinfo_get_str(handle, AIL_PROP_NAME_STR, &str);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}
	fprintf(stderr, "Package[%s], Property[%s] : %s\n", appid, property, str);

	ret = ail_destroy_appinfo(handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	return AIL_ERROR_OK;
}
 * @endcode
 */
ail_error_e ail_get_appinfo(const char *appid, ail_appinfo_h *handle);


/**
 * @fn ail_error_e ail_appinfo_get_bool(const ail_appinfo_h handle, const char *property, bool *value)
 *
 * @brief get a boolean value related to the property. 
 	Before using this API, the handle is defined by calling ail_get_appinfo.
	This function needs a out-parameter for the value.
 *
 * @par Sync (or) Async : Synchronous API.
 *
 * @param[in] handle	the handle is defined by calling ail_get_appinfo.
 * @param[in] property	 a property type of boolean
 * @param[out] value	a out-parameter value that is mapped with the property.
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_DB_FAILED				database error
 * @retval 	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 *
 * @pre define a handle using ail_get_appinfo. The handle is used as a first argument of this API.
 * @post destroy the handle with the function of ail_destroy_appinfo after using it all.
 *
 * @see  ail_get_appinfo(), ail_destroy_appinfo(), ail_appinfo_get_int(), ail_appinfo_get_str()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
static ail_error_e _get_nodisplay(const char *package)
{
	ail_appinfo_h handle;
	ail_error_e ret;
	bool value;

	ret = ail_get_appinfo(package, &handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	ret = ail_appinfo_get_bool(handle, AIL_PROP_NODISPLAY_BOOL, &value);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}
	fprintf(stderr, "Package[%s] : %d\n", package, value);

	ret = ail_destroy_appinfo(handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	return AIL_ERROR_OK;
}
 * @endcode
 */
ail_error_e ail_appinfo_get_bool(const ail_appinfo_h handle, const char *property, bool *value);



/**
 * @fn ail_error_e ail_appinfo_get_int(const ail_appinfo_h handle, const char *property, int *value)
 *
 * @brief get a integer value related to the property. 
 	Before using this API, the handle is defined by calling ail_get_appinfo.
	This function needs a out-parameter for the value.
 *
 * @par Sync (or) Async : Synchronous API.
 *
 * @param[in] handle	the handle is defined by calling ail_get_appinfo.
 * @param[in] property	a property type of integer.
 * @param[out] value	a out-parameter value that is mapped with the property.
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_DB_FAILED				database error
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 *
 * @pre define a handle using ail_get_appinfo. The handle is used as a first argument of this API.
 * @post destroy the handle with the function of ail_destroy_appinfo after using it all.
 *
 * @see  ail_get_appinfo(), ail_destroy_appinfo(), ail_appinfo_get_bool(), ail_appinfo_get_str()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
static ail_error_e _get_x_slp_baselayoutwidth(const char *package)
{
	ail_appinfo_h handle;
	ail_error_e ret;
	int value;

	ret = ail_get_appinfo(package, &handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	ret = ail_appinfo_get_int(handle, AIL_PROP_X_SLP_BASELAYOUTWIDTH_INT, &value);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}
	fprintf(stderr, "Package[%s] : %d\n", package, value);

	ret = ail_destroy_appinfo(handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	return AIL_ERROR_OK;
}
 * @endcode
 */
ail_error_e ail_appinfo_get_int(const ail_appinfo_h handle, const char *property, int *value);



/**
 * @fn ail_error_e ail_appinfo_get_str(const ail_appinfo_h handle, const char *property, char **str)
 *
 * @brief get a string related to the property. 
 	Before using this API, the handle is defined by calling ail_get_appinfo.
	This function needs a out-parameter for the value.
 *
 * @par Sync (or) Async : Synchronous API.
 *
 * @param[in] handle	the handle is defined by calling ail_get_appinfo.
 * @param[in] property	a property type of string.
 * @param[out] str		a out-parameter string that is mapped with the property. The icon property contains the absolute file path. If there is no data, the value of str is NULL.
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_DB_FAILED				database error
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 *
 * @pre define a handle using ail_get_appinfo. The handle is used as a first argument of this API.
 * @post str doesn't need to be freed. It will be freed by calling ail_destroy_appinfo.
 *
 * @see  ail_get_appinfo(), ail_destroy_appinfo(), ail_appinfo_get_bool(), ail_appinfo_get_int()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
static ail_error_e _get_nodisplay(const char *package)
{
	ail_appinfo_h handle;
	ail_error_e ret;
	char* value;

	ret = ail_get_appinfo(package, &handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	ret = ail_appinfo_get_str(handle, AIL_PROP_NAME_STR, &value);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}
	fprintf(stderr, "Package[%s] : %d\n", package, value);

	ret = ail_destroy_appinfo(handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	return AIL_ERROR_OK;
}
 * @endcode
 */
ail_error_e ail_appinfo_get_str(const ail_appinfo_h handle, const char *property, char **str);



/**
 * @fn ail_error_e ail_package_destroy_appinfo(const ail_appinfo_h handle)
 *
 * @brief destroy a handle what you get with the function of ail_package_get_appinfo.
 *
 * @par Sync (or) Async : Synchronous API.
 *
 * @param[in] handle destroy all resources related to the handle.
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_DB_FAILED				database error
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 *
 * @pre need a handle that you don't need anymore.
 * @post cannot use the handle after destroying.
 *
 * @see  ail_package_get_appinfo(), ail_appinfo_get_bool(), ail_appinfo_get_int(), ail_appinfo_get_str()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
static ail_error_e _get_name(const char *package)
{
	ail_appinfo_h handle;
	ail_error_e ret;
	char *str;

	ret = ail_package_get_appinfo(package, &handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	ret = ail_appinfo_get_str(handle, AIL_PROP_NAME_STR, &str);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}
	fprintf(stderr, "Package[%s], Property[%s] : %s\n", package, property, str);

	ret = ail_package_destroy_appinfo(handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	return AIL_ERROR_OK;
}
 * @endcode
 */
ail_error_e ail_package_destroy_appinfo(const ail_appinfo_h handle);


/**
 * @fn ail_error_e ail_destroy_appinfo(const ail_appinfo_h handle)
 *
 * @brief destroy a handle what you get with the function of ail_get_appinfo.
 *
 * @par Sync (or) Async : Synchronous API.
 *
 * @param[in] handle destroy all resources related to the handle.
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_DB_FAILED				database error
 * @retval	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 *
 * @pre need a handle that you don't need anymore.
 * @post cannot use the handle after destroying.
 *
 * @see  ail_get_appinfo(), ail_appinfo_get_bool(), ail_appinfo_get_int(), ail_appinfo_get_str()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
static ail_error_e _get_name(const char *appid)
{
	ail_appinfo_h handle;
	ail_error_e ret;
	char *str;

	ret = ail_get_appinfo(appid, &handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	ret = ail_appinfo_get_str(handle, AIL_PROP_NAME_STR, &str);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}
	fprintf(stderr, "Package[%s], Property[%s] : %s\n", appid, property, str);

	ret = ail_destroy_appinfo(handle);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	return AIL_ERROR_OK;
}
 * @endcode
 */
ail_error_e ail_destroy_appinfo(const ail_appinfo_h handle);


/**
 * @fn ail_error_e ail_desktop_add(const char *package)
 *
 * @brief add a package information into Application Information Database.
	A desktop file for this package has to be installed in the desktop directory before using this API.
	If there is no database for Application Information Database, this API will create the DB.
	If there is a DB, this function adds information for the package into the DB.
	And a notification is published to the applications who want to know about changing DB. 
 *
 * @par Sync (or) Async : Synchronous API.
 *
 * @param[in] package package name
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_FAIL					internal error
 * @retval 	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 *
 * @pre a desktop file for the package has to be installed in the desktop directory before using this API.
 * @post package information is added into the Application Information Database.
 *
 * @see  ail_desktop_update(), ail_desktop_remove()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
static ail_error_e _add_desktop(const char *package)
{
	ail_error_e ret;

	if (!package) {
		return AIL_ERROR_FAIL;
	}

	ret = ail_desktop_add(package);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	return AIL_ERROR_OK;
}
 * @endcode
 */
ail_error_e ail_desktop_add(const char *package);



/**
 * @fn ail_error_e ail_desktop_update(const char *package)
 *
 * @brief update a package information in the Application Information Database.
	A desktop file for this package has to be installed in the desktop directory before using this API.
	And a notification is published to the applications who want to know about changing DB. 
 *
 * @par Sync (or) Async : Synchronous API.
 *
 * @param[in] package package name
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_FAIL					internal error
 * @retval 	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 *
 * @pre a desktop file for the package has to be installed in the desktop directory before using this API.
 * @post update a package information in the Application Information Database.
 *
 * @see  ail_desktop_add(), ail_desktop_remove()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
static ail_error_e _update_desktop(const char *package)
{
	ail_error_e ret;

	if (!package) {
		return AIL_ERROR_FAIL;
	}

	ret = ail_desktop_update(package);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	return AIL_ERROR_OK;
}
 * @endcode
 */
ail_error_e ail_desktop_update(const char *package);



/**
 * @fn ail_error_e ail_desktop_remove(const char *package)
 *
 * @brief remove a package information in the Application Information Database.
	And a notification is published to the applications who want to know about changing DB. 
 *
 * @par Sync (or) Async : Synchronous API.
 *
 * @param[in] package package name
 *
 * @return 0 if success, negative value(<0) if fail\n
 * @retval	AIL_ERROR_OK					success
 * @retval	AIL_ERROR_FAIL					internal error
 * @retval 	AIL_ERROR_INVALID_PARAMETER		invalid parameter
 *
 * @pre no pre-condition.
 * @post package information is removed in the Application Information Database.
 *
 * @see  ail_desktop_add(), ail_desktop_update()
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
static ail_error_e _remove_desktop(const char *package)
{
	ail_error_e ret;

	if (!package) {
		return AIL_ERROR_FAIL;
	}

	ret = ail_desktop_remove(package);
	if (ret != AIL_ERROR_OK) {
		return AIL_ERROR_FAIL;
	}

	return AIL_ERROR_OK;
}
 * @endcode
 */
ail_error_e ail_desktop_remove(const char *package);

/** @} */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AIL_H__ */
// End of a file
