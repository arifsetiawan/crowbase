
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
* Write tests
* Dockerfile
* Concurrent request handling (see below)

### Concurrent request

Running concurrent apache ab test shows some issues

#### 1. Log output

```
ab -n 1000 -c 100 http://127.0.0.1:18080/hello
```

```
(2016-09-17 12:29:00) [INFO    ] Request: 127.0.0.1:49719 0x7fcbba825000 HTTP/1.0 GET /hello
(2016-09-17 12:29:00) [INFO    ] Response: 0x7fcbba825000 /hello 200 1
(2016-09-17 12:29:00) [INFO    ] Request: 127.0.0.1:49721 0x7fcbba80c000 HTTP/1.0 GET /hello
(2016-09-17 12:29:00) [INFO    ] Response: 0x7fcbba80c000 /hello 200 1
(2016-09-17 10:45:10) [INFO    ] Response: 0x7fcbba02a000 /hello 200 1
(2016-09-17 10:45:10) [INFO    ] Request: 127.0.0.1:58(921041 60-x079f-c1b7b a1807:64c50:01 0H)T T[PI/N1F.O0   G E T]  /Rheeqluleos
t:( 2102176.-00.90-.117: 51809:5495 :01x07)f c[bIbNaF0O2 c 8 0 0]  HRTeTsPp/o1n.s0e :G E0Tx 7/fhceblblao8
76(c20001 6/-h0e9l-l1o7  21000: 415
:1(02)0 1[6I-N0F9O- 1 7   1]0 :R4e5s:p1o0n)s e[:I N0FxO7 f c b b]a 0R2ecq8u0e0s t/:h e1l2l7o. 02.000. 11:
58916 0x7fcbba053400 HTTP/1.0 GET /hello
(2016-09-17 10:45:10) [INFO    ] Response: 0x7fcbba053400 /hello 200 1
```

#### 2. Couchbase 

Couchbase client seems not operate in async mode. 

```
ab -n 1000 -c 100 http://127.0.0.1:18080/users
```

```
[warn] event_base_loop: reentrant invocation.  Only one event_base_loop can run on each event_base at once.
```

## License

MIT
