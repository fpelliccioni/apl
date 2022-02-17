#pragma once

#define ct_error(err) []<bool flag = false>() {static_assert(flag, err);}
