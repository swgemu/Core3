ARG VERSION

FROM debian:bullseye

USER root

# Prep and update system
# Note to avoid java install failure we make the  /share/man pages: see https://github.com/kubernetes/kubernetes/issues/1806
RUN set -xe; \
    for i in 1 2 3 4 5 6 7 8; do mkdir -p /usr/share/man/man$i; done; \
    export UCF_FORCE_CONFFOLD=YES; \
    unset UCF_FORCE_CONFFNEW; \
    export DEBIAN_FRONTEND=noninteractive; \
    echo 'APT::Install-Recommends "0";\nAPT::Install-Suggests "0";' > /etc/apt/apt.conf.d/01norecommends; \
    apt-get update; \
    apt-get upgrade -y;

# Install build packages, using clang latest stable as /usr/bin/clang etc.
RUN set -xe; \
    apt-get install -y apt-transport-https ca-certificates git gnupg lsb-release moreutils software-properties-common wget; \
    wget -O /tmp/llvm.sh https://apt.llvm.org/llvm.sh; \
    chmod +x /tmp/llvm.sh; \
    /tmp/llvm.sh all; \
    (set +x;cd /usr/bin;for i in ../lib/llvm-*/bin/*; do ln -sfv $i .; done); \
    clang --version; \
    ld.lld --version; \
    apt-get update; \
    apt-get install -y --fix-missing \
	binutils \
	db5.3-util \
	gdb \
	less \
	strace \
	time \
        autoconf \
        automake \
        autotools-dev \
        bc \
        binutils \
        castxml \
        ccache \
        cmake \
        cpio \
        cppcheck \
        curl \
        db5.3-util \
        dnsutils \
        doxygen \
        figlet \
        file \
        g++ \
        gcc \
        gcovr \
        gdb \
        gettext-base \
        git-lfs \
        git-man \
        htop \
        iproute2 \
        iputils-ping \
        jq \
        less \
        libboost-all-dev \
        libc6 \
        libc6-dev \
        libclang-rt-16-dev \
        libcpprest-dev \
        libdb5.3 \
        libdb5.3-dev \
        libjemalloc-dev \
        libjemalloc2 \
        libmariadb-dev \
        libmariadb-dev-compat \
        libncurses5 \
        libncurses5-dev \
        libpcre3 \
        libpcre3-dev \
        libreadline-dev \
        libreadline6-dev \
        libreadline8 \
        libssl-dev \
        libssl1.1 \
        libtool \
        make \
        man \
        man-db \
        manpages \
        manpages-dev \
        mariadb-client \
        mariadb-server \
        net-tools \
        netcat \
        ninja-build \
        openjdk-11-jre-headless \
        openssh-server \
        pv \
        pwgen \
        rsync \
        runit \
        screen \
        silversearcher-ag \
        sloccount \
        strace \
        sudo \
        tcpdump \
        time \
        traceroute \
        tree \
        unzip \
        valgrind \
        vim-nox \
        wget \
    ; \
    apt-get install lua5.3 liblua5.3-0 liblua5.3-dev; \
    apt-get install lua-inspect lua-socket lua-sec lua-filesystem lua-cjson; \
    apt-get autoremove -y; \
    rm -rf /var/lib/apt/lists/* /var/log/dpkg.log* /var/log/apt/*;

ENV RUN_USER=swgemu \
    HOME_DIR=/home/swgemu \
    SHELL=/bin/bash \
    TZ=Etc/UTC \
    LANG=C.UTF-8 \
    PORT_GROUP=44

ENV STATUSPORT=${PORT_GROUP}455 \
    LOGINPORT=${PORT_GROUP}453 \
    PINGPORT=${PORT_GROUP}462 \
    ZONESERVERPORT=${PORT_GROUP}463 \
    WITH_GDB=true \
    SSHPORT=2222 \
    DBUSER=swgemu \
    ADMIN_USER=admin \
    REPOS='Core3' \
    REPO_PUBLIC_URL=https://github.com/swgemu \
    REPO_PUBLIC_BRANCH='unstable'

ENV PATH=${HOME_DIR}/bin:/usr/local/bin:${PATH}

EXPOSE ${STATUSPORT}/tcp ${LOGINPORT}/udp ${PINGPORT}/udp ${ZONESERVERPORT}/udp

COPY files /

VOLUME ${HOME_DIR}

RUN set -xe; \
    mkdir -p /var/run/mysql /var/run/mysqld; \
    chown -R mysql:mysql /var/run/mysqld; \
    chmod 777 /var/run/mysqld; \
    rm -fr /var/lib/mysql; \
    mkdir -p `dirname ${HOME_DIR}`/mysql; \
    ln -fvs ${HOME_DIR}/mysql /var/lib/mysql; \
    useradd -U ${RUN_USER} -u 44400 -G adm,sudo -s ${SHELL} -d ${HOME_DIR}; \
    echo "LANG=${LANG}" > /etc/environment; \
    sed -e '/%sudo/s/ ALL/ NOPASSWD: ALL/' -i /etc/sudoers;

ENTRYPOINT ["/run.sh"]
