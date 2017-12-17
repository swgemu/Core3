# Copyright (C) 2007 <SWGEmu>

# This File is part of Core3.

# This program is free software; you can redistribute
# it and/or modify it under the terms of the GNU Lesser
# General Public License as published by the Free Software
# Foundation; either version 2 of the License,
# or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU Lesser General Public License for
# more details.

# You should have received a copy of the GNU Lesser General
# Public License along with this program; if not, write to
# the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

# Linking Engine3 statically or dynamically with other modules
# is making a combined work based on Engine3.
# Thus, the terms and conditions of the GNU Lesser General Public License
# cover the whole combination.

# In addition, as a special exception, the copyright holders of Engine3
# give you permission to combine Engine3 program with free software
# programs or libraries that are released under the GNU LGPL and with
# code included in the standard release of Core3 under the GNU LGPL
# license (or modified versions of such code, with unchanged license).
# You may copy and distribute such a system following the terms of the
# GNU LGPL for Engine3 and the licenses of the other code concerned,
# provided that you include the source code of that other code when
# and as the GNU LGPL requires distribution of source code.

# Note that people who make modified versions of Engine3 are not obligated
# to grant this special exception for their modified versions;
# it is their choice whether to do so. The GNU Lesser General Public License
# gives permission to release a modified version without this exception;
# this exception also makes it possible to release a modified version
# which carries forward this exception.


IDLC = ../MMOEngine/bin/idlc

IDL_CLASSPATH = ../MMOEngine/include

#IDL_DIRECTIVES = -noprelocks -makefile src/Makefile.am -outdir autogen -cp $(IDL_CLASSPATH)
IDL_DIRECTIVES = -makefile src/Makefile.am -outdir autogen -cp $(IDL_CLASSPATH)

UNITTEST_DIRECTIVES =

all: #build
	#cd build/unix && cmake ../.. && make
	#cp build/unix/src/core3 bin

build: idl gtest gitlog
	cd build/unix && make -j4 UNITTEST_DIRECTIVES="$(UNITTEST_DIRECTIVES)" #CC=clang CXX=clang++
	cp build/unix/src/core3* bin
	rm build/unix/src/core3
	rm build/unix/src/core3client
	#done

unittest: UNITTEST_DIRECTIVES = -fprofile-arcs -ftest-coverage
unittest: build

unittest-cmake: UNITTEST_DIRECTIVES = -fprofile-arcs -ftest-coverage
unittest-cmake: build-cmake

sanitizers-cmake: UNITTEST_DIRECTIVES = -fsanitize=address 
sanitizers-cmake: build-cmake

rebuild: clean build

gitlog: 
	cd bin/conf && git log --pretty=format:'%h was %an, %ar, message: %s' -10 > rev.txt

idl:
	$(IDLC) $(IDL_DIRECTIVES) -sd src anyadEclipse
	#done

gtest:
	cd utils/googletest-release-1.8.0/googlemock && ${MAKE} all

config:
	aclocal
	automake --add-missing
	autoreconf --force --install
	cd build/unix && ../../configure
	#cd ../MMOEngine/external/ptmalloc3 && make
	#done

clean: cleanidl
	cd build/unix && ${MAKE} clean
	cd utils/googletest-release-1.8.0/googlemock && ${MAKE} clean
	#cd build/unix/src && rm *
	#cd build/unix/src/.deps && rm *
	#done

cleanidl:
	$(IDLC) -rebuild $(IDL_DIRECTIVES) -sd src anyadEclipse

cleardb:
	cd bin/databases && rm -rf *.*
	#done

PLATFORM:=$(shell uname -s)

build-cmake: idl
	cd build/unix && cmake -DBUILD_IDL=OFF -DRUN_GIT=ON -DCMAKE_CXX_FLAGS="$(UNITTEST_DIRECTIVES)" ../.. && ${MAKE}
	#done

build-cmake-with-idl:
	cd build/unix && cmake -DBUILD_IDL=ON -DRUN_GIT=ON -DCMAKE_CXX_FLAGS="$(UNITTEST_DIRECTIVES)" ../.. && ${MAKE}
	#done

clean-cmake:
	rm -f build/unix/CMakeCache.txt
	rm -f build/unix/cmake_install.cmake
	rm -f build/unix/Makefile
	rm -rf build/unix/CMakeFiles
	#done

DB_NAMESPACE=
DB_IMAGE=

APP_NAMESPACE=swgemu
APP_NAME=core3
APP_IMAGE=akimaki/swgemu-core3:1.0

build-docker:
	sudo docker build -t ${APP_IMAGE} docker
	sudo docker push ${APP_IMAGE}
	sudo docker images | grep "<none>" | awk '{print $$3}' | xargs sudo docker rmi
	#done

init-storage:
	kubectl create -f helm/storage-class.yaml --validate=false
	#done

init-db-helm:
	kubectl create namespace ${DB_NAMESPACE}
	kubectl create serviceaccount --namespace ${DB_NAMESPACE} tiller
	kubectl create clusterrolebinding tiller-cluster-rule-${DB_NAMESPACE} --clusterrole=cluster-admin --serviceaccount=${DB_NAMESPACE}:tiller
	helm init --service-account=tiller --tiller-namespace=nuodb
	#done

deploy-db-helm:
	helm install helm/${DB_NAMESPACE} --tiller-namespace ${DB_NAMESPACE} --name ${DB_NAMESPACE} --namespace ${DB_NAMESPACE}
	#done

shutdown-db-helm:
	helm delete ${DB_NAMESPACE} --tiller-namespace ${DB_NAMESPACE} --purge
	#done

init-app-helm:
	kubectl create namespace $(APP_NAMESPACE)
	kubectl create serviceaccount --namespace $(APP_NAMESPACE) tiller
	kubectl create clusterrolebinding tiller-cluster-rule-$(APP_NAMESPACE) --clusterrole=cluster-admin --serviceaccount=$(APP_NAMESPACE):tiller
	helm init --service-account=tiller --tiller-namespace=$(APP_NAMESPACE)
	#done

deploy-app-helm:
	helm install helm/${APP_NAME} --tiller-namespace $(APP_NAMESPACE) --name $(APP_NAME) --namespace $(APP_NAMESPACE)
	#done

shutdown-app-helm:
	helm delete $(APP_NAME) --tiller-namespace $(APP_NAMESPACE) --purge
	#done

purge-app-helm:
	kubectl delete clusterrolebinding tiller-cluster-rule-$(APP_NAMESPACE)
	kubectl delete serviceaccount --namespace $(APP_NAMESPACE) tiller
	kubectl delete namespace $(APP_NAMESPACE)
	#done

status-db-helm:
	helm ls --all --tiller-namespace ${DB_NAMESPACE}
	kubectl get svc --namespace ${DB_NAMESPACE}
	kubectl get po --namespace ${DB_NAMESPACE}
	kubectl exec nuodb-sm-0 --namespace nuodb -- /opt/nuodb/bin/nuodbmgr --broker localhost --password bird --command "show domain summary"
	#done 

status-app-helm:
	helm ls --all --tiller-namespace $(APP_NAMESPACE)
	kubectl get svc --namespace $(APP_NAMESPACE)
	kubectl get po --namespace $(APP_NAMESPACE)
	#done

exec-app:
	kubectl exec core3-zone-0 -n swgemu -ti -- bash

pv-nuodb:
	kubectl get pv | grep nuodb/nuodb-var-nuodb-sm | awk '{print $$1}' | xargs -I ID kubectl describe pv ID | grep "Path:" | awk '{ print $$2 }'
	#done
