FROM debian:jessie

RUN echo 'APT::Install-Recommends "0";\nAPT::Install-Suggests "0";' > /etc/apt/apt.conf.d/01norecommends

RUN apt-get update && apt-get upgrade -y

RUN echo "mysql-server mysql-server/root_password password root" | debconf-set-selections
RUN echo "mysql-server mysql-server/root_password_again password root" | debconf-set-selections

RUN apt-get install -y gcc g++ make autoconf automake autotools-dev git libc6-dev libdb5.3-dev libreadline-dev libmysqlclient-dev libssl-dev git vim openjdk-7-jre-headless gdb gccxml mysql-server

#RUN find /var/lib/mysql -type f -exec touch {} \; && service mysql start

#RUN echo 'CREATE DATABASE swgemu;' | mysql -uroot -proot
#RUN echo 'GRANT ALL ON *.* TO `swgemu`@`localhost` IDENTIFIED BY "123456";' | mysql -uroot -proot

RUN mkdir -p /swgemu/MMOEngine && mkdir -p /swgemu/MMOCoreORB
#RUN ln -s /swgemu/MMOEngine/bin/idlc /usr/local/bin/idlc

RUN apt-get install -y wget && wget http://www.lua.org/ftp/lua-5.3.3.tar.gz && tar -xvf lua-5.3.3.tar.gz && cd lua-5.3.3 && make linux install && cd .. && rm -R lua-5.3.3 && rm lua-5.3.3.tar.gz && ldconfig

RUN mkdir -p /home/swgemu/workspace/tre

#RUN apt-get install -y clang-3.5

RUN mkdir git && cd git && git clone http://review.swgemu.com/p/Core3.git && git clone http://review.swgemu.com/p/PublicEngine.git && cd PublicEngine/MMOEngine && make && chmod +x bin/idlc && cp bin/idlc /usr/local/bin/idlc && cd ../../Core3 && git checkout unstable && ln -s ../PublicEngine/MMOEngine MMOEngine

ENV CLASSPATH="/git/PublicEngine/MMOEngine/bin/idlc.jar"
RUN echo 'export CLASSPATH="/git/PublicEngine/MMOEngine/bin/idlc.jar"' >> /root/.profile

RUN cd git/Core3/MMOCoreORB && make config && make build

RUN apt-get install -y supervisor

# copy the supervisor conf file into the image
ADD scripts/supervisord-core3.conf /etc/supervisor/conf.d/supervisord-core3.conf

ADD scripts/run.sh /tmp/
RUN /bin/chmod +x /tmp/run.sh
CMD /tmp/run.sh
