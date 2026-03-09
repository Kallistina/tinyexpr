FROM aflplusplus/aflplusplus:latest

WORKDIR /src

COPY tinyexpr.c tinyexpr.h ./
COPY fuzz/fuzz_tinyexpr.c ./
COPY fuzz/seeds /seeds

RUN afl-clang-fast -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer \
    -I/src -o /fuzz_tinyexpr /src/fuzz_tinyexpr.c /src/tinyexpr.c -lm

RUN mkdir -p /out

ENV AFL_SKIP_CPUFREQ=1
ENV AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1

CMD ["afl-fuzz", "-i", "/seeds", "-o", "/out", "--", "/fuzz_tinyexpr", "@@"]
