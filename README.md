Sublime Build:
```
{
    "build_systems":
    [
        {
            "working_dir": "/home/kuba/PRJ/cpp_rozne/qt_MV_tree/build",
            "file_regex": "([/0-9a-zA-Z._]+):(\\d+):(\\d+): error",      //jumps to error line in a file
            // "line_regex": "undefined",                                //jumps to error line
            "name": "1 make",
            // "shell_cmd": "make -w 2>&1 | ./make_abs.py",     // only needed if make file returns indirect paths (usually with SUBTARGETS)
            "shell_cmd": "make -w",
            "syntax": "Packages/Makefile.sublime-package_FILES/Make.build-language"
        },
        {
            // "env":
            // {
            //     "LD_LIBRARY_PATH": "/home/kuba/SRC/qtfm/build-5_10-Debug/libfm:|$LD_LIBRARY_PATH"
            // },
            "name": "2 run",
            "working_dir": "/home/kuba/PRJ/cpp_rozne/qt_MV_tree/build",
            "shell_cmd": "./helloworld"
        },
        {
            "name": "3 cmake",
            "shell_cmd": "cmake ..",
            "working_dir": "/home/kuba/PRJ/cpp_rozne/qt_MV_tree/build",
            "variants":
                [
                    {
                    "name": "cmake clean",
                    "shell_cmd": "rm -rf * && cmake ..",
                    },
                ]
        },
        {
            "name": "4 qmake",
            // "shell_cmd": "/home/kuba/toolchains/qt510/bin/qmake /home/kuba/SRC/qtfm/qtfm.pro  CONFIG+=debug CONFIG+=no_ffmpeg",
            // "working_dir": "/home/kuba/SRC/qtfm/build"
        },
        {
            "env":
            {
                "PATH": "$HOME/.config/sublime-text-3/Packages/User/:$PATH"
            },
            "name": "5 testowy",
            "shell_cmd": "testowy.py",
        },
    ],
    "folders":
    [
        {
            "path": "/home/kuba/PRJ/cpp_rozne/qt_MV_tree"
        },
        {
            "path": "/home/kuba/toolchains/qt510/include"
        }
    ]
}
```