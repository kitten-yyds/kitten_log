# Kitten Log
![img](./img/img.png)

## 语言
[English](./readme.md)

## 概览
这是一个适用于嵌入式系统的小巧、易用的日志库。

Kitten Log 提供一个简洁的日志 API，支持多种日志级别、格式化消息、可选时间戳、彩色输出，以及由应用程序提供的输出函数。

## 特点
- 轻量的C语言实现
- 不使用动态内存分配
- 四个日志级别：
    - 调试
    - 信息
    - 警告
    - 错误
- 支持 `printf` 风格的格式化消息
- 可选毫秒或秒为单位的时间戳
- 日志级别支持 ANSI 颜色代码
- 不依赖 UART、USB 或其他传输层实现
- 适用于 UART、USB CDC、半主机（semihosting）或其他输出设备

## 包内文件
- `kitten_log.h`：公共 API 和配置宏
- `kitten_log.c`：核心实现

## 快速开始
Kitten Log 只包含核心日志功能，不提供硬件相关的输出驱动，输出函数需由应用程序自行实现。

### 1. 添加源文件
将 `kitten_log.c` 添加至您的构建系统，并将包含 `kitten_log.h` 的目录添加到包含路径（头文件搜索路径）中。

### 2. 实现输出函数
应用程序必须实现 `platform_kitten_log_print()`.

```c
#include "kitten_log.h"

void platform_kitten_log_print(const char *text, unsigned int length)
{
    /*
     * 将恰好 `length` 个字节发送到 UART、USB CDC、半主机（semihosting）、
     * 文件或其他输出设备。
     */
}
```

`length` 参数指定了要传输的字节数，它不包含结尾的空字符（`'\0'`）。输出函数应准确发送 `length` 个字节。

### 3. 使用日志宏
```c
#include "kitten_log.h"

KITTEN_LOGE("main", "this is an error msg");
KITTEN_LOGW("main", "this is a warning msg");
KITTEN_LOGI("main", "this is an information msg");
KITTEN_LOGD("main", "this is a debug msg");
```

示例输出：
```
[E][main]: this is an error msg
[W][main]: this is a warning msg
[I][main]: this is an information msg
[D][main]: this is a debug msg
```

> **提示：** `tag` 参数可以是任意的字符串，建议使用源文件名或模块名。

> **笔记：** 可以使用 `__func__` 自动获取当前函数的名称。

### 4. 可选的时间戳打印
时间戳打印默认为禁用状态。如需启用时间戳，需要定义 `KITTEN_LOG_TIME` 宏。

然后您可以通过定义 `KITTEN_LOG_TIME_MS` 或 `KITTEN_LOG_TIME_S` 来选择使用毫秒或秒为单位的时间戳。

> **警告：** 当定义了 `KITTEN_LOG_TIME` 时，必须且只能定义 `KITTEN_LOG_TIME_MS` 和 `KITTEN_LOG_TIME_S` 中的其中一个。如果两者都定义或都未定义，将导致编译错误。

> **笔记：** 如果您使用GNU make，您可以在 Makefile 中定义这些宏

## API 参考
### Log 宏
- `KITTEN_LOGD(tag, format, ...)`：打印一条调试（debug）信息
- `KITTEN_LOGI(tag, format, ...)`：打印一条信息（info）信息
- `KITTEN_LOGW(tag, format, ...)`：打印一条警告（warning）信息
- `KITTEN_LOGE(tag, format, ...)`：打印一条错误（error）信息

### 类型
- `enum kitten_log_level`
- `KITTEN_LOG_LEVEL_DEBUG`
- `KITTEN_LOG_LEVEL_INFO`
- `KITTEN_LOG_LEVEL_WARN`
- `KITTEN_LOG_LEVEL_ERROR`

### 函数
#### `void kitten_log(enum kitten_log_level level, const char *tag, const char *format, ...);`
格式化并打印一条日志条目。

#### `void platform_kitten_log_print(const char *text, unsigned int length);`
由应用程序提供的输出函数。`length` 是要传输的字节数，不包含末尾的 `'\0'`。

#### `uint32_t platform_kitten_log_get_time_ms(void);`
仅在启用 KITTEN_LOG_TIME 时需要实现。返回当前时间的毫秒值。

### 常量和配置宏
- `KITTEN_LOG_BUF_SIZE`：内部固定缓冲区大小，当前为 `256`
- `KITTEN_LOG_TIME`：启用时间戳
- `KITTEN_LOG_TIME_MS`：以毫秒为单位输出时间戳
- `KITTEN_LOG_TIME_S`：以秒为单位输出时间戳

当定义了 `KITTEN_LOG_TIME` 时，必须且只能同时定义 `KITTEN_LOG_TIME_MS` 或 `KITTEN_LOG_TIME_S` 中的其中一个。

## 限制
- 完整的格式化日志条目必须能容纳在 256 字节的缓冲区中，不支持过大的日志消息。
- 无动态内存分配。
- 无内置日志等级过滤。
- 无内部锁，并发调用需在外部串行化。
- 核心模块同步调用输出函数；若传输是阻塞式的，则可能阻塞调用者。
- ANSI 颜色代码需要兼容的终端支持。
- 时间戳基于应用程序提供的时间函数返回值，而不一定是实际的挂钟时间（wall‑clock time）。

## 贡献者
kitten-yyds

![kitten-yyds logo](./img/kitten-yyds.png)