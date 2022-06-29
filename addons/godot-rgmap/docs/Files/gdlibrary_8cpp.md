---
title: /home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/gdlibrary.cpp

---

# /home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/gdlibrary.cpp



## Functions

|                | Name           |
| -------------- | -------------- |
| void GDN_EXPORT | **[godot_gdnative_init](Files/gdlibrary_8cpp.md#function-godot-gdnative-init)**(godot_gdnative_init_options * o) |
| void GDN_EXPORT | **[godot_gdnative_terminate](Files/gdlibrary_8cpp.md#function-godot-gdnative-terminate)**(godot_gdnative_terminate_options * o) |
| void GDN_EXPORT | **[godot_nativescript_init](Files/gdlibrary_8cpp.md#function-godot-nativescript-init)**(void * handle) |


## Functions Documentation

### function godot_gdnative_init

```cpp
void GDN_EXPORT godot_gdnative_init(
    godot_gdnative_init_options * o
)
```


### function godot_gdnative_terminate

```cpp
void GDN_EXPORT godot_gdnative_terminate(
    godot_gdnative_terminate_options * o
)
```


### function godot_nativescript_init

```cpp
void GDN_EXPORT godot_nativescript_init(
    void * handle
)
```




## Source code

```cpp
#include "rgmap.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    godot::register_class<godot::RGMap>();

}
```


-------------------------------

Updated on 2022-06-29 at 17:56:25 +0300
