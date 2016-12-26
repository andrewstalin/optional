# Overview

Optional a temporary solution until the с++17 release.

# Example

Use in Windows

```c++
auto handle = ::CreateFile(path, FILE_GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
THROW_IF(handle == INVALID_HANDLE_VALUE, WIN32_ERROR("CreateFile"));
```
Use in Linux/Mac Os

```c++
auto fd = ::open(path, flags);
THROW_IF(fd == -1, POSIX_ERROR("open"));
```

ErrorOrValue example

```c++
int fun();

...

try
{
    return optional::ErrorOrValue<int>(fun());
}
catch(...)
{
    return optional::ErrorOrValue<int>(std::current_exception());
}
```
