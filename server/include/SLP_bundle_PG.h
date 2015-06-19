/*
 * bundle
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Jayoun Lee <airjany@samsung.com>, Sewook Park <sewook7.park@samsung.com>,
 * Jaeho Lee <jaeho81.lee@samsung.com>
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
 *
 * @ingroup SLP_PG
 * @defgroup bundle_PG Bundle
 * @brief A simple string-based dictionary ADT
 * @{

<h1 class="pg">Introduction</h1>
bundle is a simple dictionary ADT to be used in UI-gadget, AUL, and other libraries in application framework. <br>
bundle can store a number of string key-value pairs, get value by key, duplicate itself, and encode/decode to convert itself into binary data. <br>


<h1 class="pg">Functional architecture diagram</h1>
\image html SLP_bundle_PG_image01.png "Picture 1. Functional architecture"

A bundle object, created by bundle_create(), can add/delete key/value pairs, get a value with a key, and get number of key/value pairs in it. <br>
A bundle object can be duplicated by bundle_dup(). <br>
bundle_encode() can encode a bundle object into byte code(bundle_raw == unsigned char *). This byte code can be decoded into a new bundle object, by bundle_decode(). <br>
All bundle objects must be freed by bundle_free(). <br>

<h1 class="pg">Features</h1>
<ul>
	<li>Only string type is allowed for key and value.</li>
	<li>Each key and value is duplicated into the bundle object.</li>
	<li>Unlimited number of key/value pairs. (Memory limit is still to be considered)</li>
	<li>No key overlap : You cannot assign new values with existing key.</li>
</ul>

<h1 class="pg">API list and description</h1>
<ul>
	<li>bundle_create() : Create a bundle object.</li>
	<li>bundle_free() : Free a bundle object.</li>
	<li>bundle_add() : Add a key/value pair into the bundle object.</li>
	<li>bundle_del() : Delete a key/value pair by given key from the bundle object.</li>
	<li>bundle_get_val() : Get a value by key.</li>
	<li>bundle_get_count() : Get number of key/value pairs in the bundle object.</li>
	<li>bundle_dup() : Duplicate give bundle object</li>
	<li>bundle_iterate() : Run iterator function for each key/value pair in the bundle object.</li>
	<li>bundle_encode() : Encode bundle object into a byte code.</li>
	<li>bundle_decode() : Decode byt code into a bundle object.</li>
	<li></li>
</ul>

<h1 class="pg">Sample code</h1>
bundle library is very easy to use, and the sample code below would enough to understand how to use bundle. <br>
Detailed API instructions are in API reference in doxygen document.
<h2 class="pg">Note</h2>
<ul>
	<li>Only string type(char *) keys/values are allowed.</li>
	<li>A bundle object must be freed certainly by bundle_free(). </li>
	<li>Values retrived by bundle_get_val() cannot be modified.<br> If you want to modify value string, duplicate it.</li>
</ul>
<h2 class="pg">Code</h2>
@code
#include <stdio.h>
#include <bundle.h>

// This is a sample iterator callback function
void print_bundle_item(const char *key, const char *val, void *data);

// Sample code
int
main(int argc, char **argv)
{
	char *str;
	int count;

	bundle *b, *b_dup;

	// Create a new bundle object
	b = bundle_new();

	// Add a string with key "a"
	bundle_add(b, "a", "123abc");

	// Add another string with key "b"
	bundle_add("b", "456def");

	// str = "123abc"
	// You cannot modify string!
	str = bundle_get_val(b, "a");

	// Run iterator function with each items
	bundle_iterate(b, print_bundle_item, NULL);

	// count = 2
	count = bundle_get_count(b);
	
	// Delete an item with key "a"
	bundle_del(b, "a");

	// count = 1
	count = bundle_get_count(b);

	// If "a" key is requested, NULL is returned
	// str = NULL, errno = ENOKEY
	str = bundle_get_val(b, "a");

	// Duplicate bundle object
	b_dup = bundle_dup(b);

	// Free bundle objects
	bundle_free(b);
	bundle_free(b_dup);

	return 0;
}

void
print_bundle_item(const char *key, const char *val, void *data)
{
	printf("%s -> %s\n", key, val);
}
@endcode

 * @}
 */
