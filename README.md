# Projup [![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
Projup is a simple project setuper that can setup a project from a template.

# Build from soruce and install

```
cmake .
make
sudo ./install.sh
```

# Usage

To create a simple c project with projup, you can run the following command:
```c
projup my_project c
```

# Create a template project
If you want, you can create your own template that can be used to create new projects.

For the example I create a C template.
First create a folder in the `/etc/projup/templates` directory that called `c` (or your template name).

So the folder structure should be looks like this:
```
/etc/projup/templates/
└── c
```

And now you can create any file in the `c` folder. Because when you run `projup my_project c` it will create a folder called `my_project` and copy all the files from the `template/c` folder into the `my_project` folder and then the projup will replace the variables with values.

When creating the files in the `c` folder, you can use [variables](https://github.com/TheKruger/projup#variables) and also you can add your own variables.

Now I create a `main.c` file in the `c` folder and put the following code:
```c
// main.c

#include <stdio.h>

int main() {
    printf("Hello from $NAME!\n");
    return 0;
}

```

### Projup file
The projup file is basicly just an sh file. You can use this file to execute commands when the files are copied.
Simply create a file in the `c` (or in your template) folder called `projup` and put the following code for example:
```sh
mkdir bin
mkdir include
```
And also you can use variables but instead of using the `$` character you only can use `@` character, because `$` is reserved for variables in bash.

This file always gets executed if the file exists and when the files are copied.
The file should be in the root of the template folder.
```
/etc/projup/templates/
└── c
    └── projup
    └── main.c
    ...
```

# Variables
These variables are built-in the `projup` and can be used in the files.

Note: These variables are not contains quotes.

| Variable | Description | Example |
| - | - | - |
| `$NAME` | The name of the project. | `my_project` |
| `$TEMPLATE` | The name of the template. | `c` |

If you want to add custom variables, you can add them by running the following command:
```
projup my_project c my_variable=my_value a=1
```

So when the program runs, it will replace `$my_variable` with `my_value` and `$a` with `1` in the template files.

# Contributing
If you want to contribute the project with templates or with any useful features, you can create a pull request.