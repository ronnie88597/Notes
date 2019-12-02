# How to get current work directory?

```c++
#include <unistd.h>
#include <linux/limits.h> // where macro PATH_MAX defined.
char Cwd[PATH_MAX];
getcwd(Cwd, PATH_MAX);
```