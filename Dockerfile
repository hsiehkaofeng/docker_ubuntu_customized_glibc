FROM ubuntu:18.04

MAINTAINER khsieh

#install dependencies
RUN apt-get update && \
    #apt-get install -y --no-install-recommends apt-utils && \
    apt-get install -y build-essential && \
    apt-get install -y bison && \
    apt-get install -y gawk && \
    apt-get install -y python3

#create ld.so.conf
RUN mkdir -p /usr/local/etc/
RUN touch /usr/local/etc/ld.so.conf


WORKDIR /home/glibc/glibc-2.27

COPY glibc_2.27/glibc-2.27 .

WORKDIR /home/glibc/glibc-build

# --prefix : location defaults to /usr/local
#RUN ../glibc-2.27/configure --disable-sanity-checks --disable-werror
# overwrite the original glibc
RUN ../glibc-2.27/configure --prefix=/ --disable-sanity-checks --disable-werror
RUN make -j4

RUN make install

#overwrite the original ld in lib64
WORKDIR /lib64

RUN cp /lib/ld-linux-x86-64.so.2 .



WORKDIR /home/app

COPY vma_test.c .

RUN gcc vma_test.c -o vma_test -lpthread

CMD ["/home/app/vma_test"]


