mkdir -p bin
em++ -Iabseil-cpp -Is2geometry/src -lembind \
    -DNDEBUG -DEMSCRIPTEN_HAS_UNBOUND_TYPE_NAMES=0 \
    --no-entry -g0 -Oz -flto -sWASM_BIGINT=1 \
    -sASSERTIONS=0 -sSAFE_HEAP=0 -sSTACK_OVERFLOW_CHECK=0 \
    -sFILESYSTEM=0 -sSUPPORT_ERRNO=0 -sMINIMAL_RUNTIME=2 \
    -fno-rtti -fno-exceptions \
    abseil-cpp/absl/base/internal/raw_logging.cc \
    abseil-cpp/absl/base/internal/spinlock_wait.cc \
    s2geometry/src/s2/s1angle.cc \
    s2geometry/src/s2/s2coords.cc \
    s2geometry/src/s2/s2cell_id.cc \
    s2geometry/src/s2/s2latlng.cc \
    main.cpp \
    -sEXPORT_NAME=InitS2 -sMODULARIZE=1 -sENVIRONMENT=web -o bin/s2.js