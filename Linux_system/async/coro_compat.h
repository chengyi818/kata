// coro_compat.h — C++20 协程兼容层
// 解决 GCC 10 / Clang 13 + libc++ 的 <coroutine> 头文件兼容问题
// Pi (Debian 11) 上 GCC 10 的 <coroutine> 需要 -fcoroutines，
// 而 Clang 13 的 libc++ 只有 <experimental/coroutine>。

#pragma once

#if defined(__clang__) && __has_include(<experimental/coroutine>)
  // Clang + libc++: 使用 experimental 并引入 std 命名空间
  #include <experimental/coroutine>
  namespace std {
    using std::experimental::coroutine_handle;
    using std::experimental::coroutine_traits;
    using std::experimental::suspend_always;
    using std::experimental::suspend_never;
  }
#elif __has_include(<coroutine>)
  #include <coroutine>
#else
  #error "No coroutine header found"
#endif
