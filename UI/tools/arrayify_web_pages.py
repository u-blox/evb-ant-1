import os

header = """
/*
* Copyright 2023 u-blox
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
*/

#include <httpsrv_fs.h>

extern const HTTPSRV_FS_DIR_ENTRY httpsrv_fs_data[];
"""

end = """
const HTTPSRV_FS_DIR_ENTRY httpsrv_fs_data[] = {
    {"/index.html", 0, (unsigned char *)httpsrv_fs_webpage_my_index_html, sizeof(httpsrv_fs_webpage_my_index_html) - 1},
    {"/style.css", 0, (unsigned char *)httpsrv_fs_webpage_my_style_css, sizeof(httpsrv_fs_webpage_my_style_css) - 1},
    {"/evbConf.js", 0, (unsigned char *)httpsrv_fs_webpage_evb_conf_js, sizeof(httpsrv_fs_webpage_evb_conf_js) - 1},
    {"/favicon-16x16.png", 0, (unsigned char *)httpsrv_fs_webpage_my_favicon, sizeof(httpsrv_fs_webpage_my_favicon)},
    {0, 0, 0, 0}
};
"""

res = os.system("arrayify ../index.html -n httpsrv_fs_webpage_my_index_html -l 120 -o httpsrv_fs_webpage_my_index_html.c -b")
res = os.system("arrayify ../evbConf.js -n httpsrv_fs_webpage_evb_conf_js -l 118 -o httpsrv_fs_webpage_evb_conf_js.c -b")
res = os.system("arrayify ../style.css -n  httpsrv_fs_webpage_my_style_css -l 119 -o httpsrv_fs_webpage_my_style_css.c -b")

with open('httpsrv_fs_webpage_my_index_html.c', 'r') as index, open('httpsrv_fs_webpage_evb_conf_js.c', 'r') as js, open('httpsrv_fs_webpage_my_style_css.c', 'r') as css, open('../httpsrv_fs_favicon.c', 'r') as fav:
    with open('../../source/app/bip_httpsrv_fs_data.c', 'w') as f:
        f.write(header)
        f.write(index.read())
        f.write('\n')
        f.write(js.read())
        f.write('\n')
        f.write(css.read())
        f.write('\n')
        f.write(fav.read())
        f.write('\n')
        f.write(end)
        f.write('\n')

# Cleanup after ourselves
os.remove('httpsrv_fs_webpage_my_index_html.c')
os.remove('httpsrv_fs_webpage_evb_conf_js.c')
os.remove('httpsrv_fs_webpage_my_style_css.c')
