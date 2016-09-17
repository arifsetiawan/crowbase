
# Crowbase

Not so simple C++ server project with [Crow library](https://github.com/ipkn/crow) and Couchbase

## Couchbase

You can choose methods convenient to you to install Couchbase, here I use Docker.

```
docker pull couchbase/server:4.5.0
```

Start a container

```
docker run -d --name couchbase -p 8091-8094:8091-8094 -p 11210:11210 couchbase/server:4.5.0
```

See [here](https://github.com/couchbase/docker/tree/master/enterprise/couchbase-server/4.5.0) for setup reference

If you are using Docker Machine, you might need to replace `localhost` with your docker machine ip. Use `docker-machine ip default`. Depending on your host spec, you can custom RAM Quota.

### Couchbase bucket

Go to Couchbase dashboard at http://192.168.99.100:8091/ (192.168.99.100 is my Docker Machine IP, yours might differ). Create new bucket and set password.

## Third party dependencies

To be able to compile this project, you need to download all external dependencies.

**Note** I use OSX 10.11 with Compiler AppleClang 7.3.0.7030029

### Boost

```
brew install boost
```

### CMake

https://cmake.org/download/

### Crow

[Crow](https://github.com/ipkn/crow) is C++ microframework for web application. To setup Crow as dependency

```
mkdir external
cd external
git clone https://github.com/ipkn/crow.git
```

Note that this will always pull the latest commit on master branch. This project is using commit hash 806ef51092fd94c0788d5b4821331353c3ee127a. Crow don't maintain version yet

### JSON

We use Modern JSON library from https://github.com/nlohmann/json

```
cd external
git clone https://github.com/nlohmann/json.git
cd json
git checkout master
```

### Couchbase client

```
cd external
https://github.com/couchbase/libcouchbase.git
https://github.com/couchbaselabs/libcouchbase-cxx.git
```

Build libcouchbase. See https://github.com/couchbase/libcouchbase#dependencies and https://github.com/couchbase/libcouchbase#building-on-unix-like-systems

Or install with brew
```
brew install libcouchbase
```

### Cpp toml

```
cd external
git clone https://github.com/skystrife/cpptoml.git
```

## Build

**Note** Update [toml config](config/config.toml) file with appropriate value before continue!

To build project, clone repository and do this steps:
```bash
mkdir build && cd build
cmake ..
make
```

Run the app
```
./crowbase
```

## Run tests

## Authors

* Nurul Arif Setiawan <n.arif.setiawan@gmail.com>

## Known issues

* Better CMake
* More tests
* Profiling
* Dockerfile

## License

MIT
