# Projup
Projup is a simple project setuper that can setup a project from a template.

# Build from soruce and install

```
cmake .
make
chmod +x install.sh
sudo ./install.sh
```

# Usage

To create a simple c project with projup, you can run the following command:
```c
projup my_project c
```

# Create a template project
If you want you can create your own template project that can be used to create new projects.

For the example I create a C template.

First create a folder in the `templates` folder that called `c`.

So the folder structure should be looks like this:
```
/etc/projup/templates/
└── c
```

And now you can create any file in the `c` folder. Because when you run `projup my_project c` it will create a folder called `my_project` and copy all the files in the `c` folder to the `my_project` folder and replace the variables.

When creating the files in the `c` folder, you can use [variables](https://github.com/TheKruger/projup#variables). And also you can add your own variables.

Now I create a `main.c` file in the `c` folder and put the following code:
```c
// main.c

#include <stdio.h>

int main() {
    printf("Hello from $NAME!\n");
    return 0;
}

```

# Variables
These variables are built in the `projup` and can be used in the files.

Note: These variables are not contains quotes.

| Variable | Description | Example |
| --- | --- |
| `$NAME` | The name of the project. | `my_project` |
| `$TEMPLATE` | The name of the template. | `c` |

If you want to add custom variables, you can add them to the by running the following command:
```
projup my_project c my_variable=my_value a=1
```

So when the program runs, it will replace `$my_variable` with `my_value` and `a` with `1` in the template files.

# Contributing
If you want to contribute the project with templates or with any useful features, you can create a pull request.