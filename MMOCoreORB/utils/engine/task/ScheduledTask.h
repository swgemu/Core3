#ifndef SCHEDULEDTASK_H_
#define SCHEDULEDTASK_H_


#include <boost/typeof/typeof.hpp>

#include <signal.h>

#include "system/lang.h"

#include "system/util/Timer.h"


#define SCHEDULE_TASK_1(Param1, Time, Code) \
        { \
        class Param1##Param1 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
        public: \
                Param1##Param1(param1_type param1) : Param1##_p(param1) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Param1##Param1* task = new Param1##Param1(Param1); \
        task->schedule(Time); \
        }


#define SCHEDULE_TASK_2(Param1, Param2, Time, Code) \
        { \
        class Param1##Param2 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param2) param2_type; \
				param2_type Param2##_p; \
        public: \
                Param1##Param2(param1_type param1, param2_type param2) : Param1##_p(param1), Param2##_p(param2) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Param1##Param2* task = new Param1##Param2(Param1, Param2); \
        task->schedule(Time); \
        }


#define SCHEDULE_TASK_3(Param1, Param2, Param3, Time, Code) \
        { \
        class Param1##Param2##Param3 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param2) param2_type; \
                param2_type Param2##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param3) param3_type; \
				param3_type Param3##_p; \
        public: \
                Param1##Param2##Param3(param1_type param1, param2_type param2, param3_type param3) : Param1##_p(param1), Param2##_p(param2), Param3##_p(param3) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Task* task = new Param1##Param2##Param3(Param1, Param2, Param3); \
        task->schedule(Time); \
        }


#define SCHEDULE_TASK_4(Param1, Param2, Param3, Param4, Time, Code) \
        { \
        class Param1##Param2##Param3##Param4 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param2) param2_type; \
                param2_type Param2##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param3) param3_type; \
                param3_type Param3##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param4) param4_type; \
				param4_type Param4##_p; \
        public: \
                Param1##Param2##Param3##Param4(param1_type param1, param2_type param2, param3_type param3, param4_type param4) : Param1##_p(param1), Param2##_p(param2), Param3##_p(param3), Param4##_p(param4) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Task* task = new Param1##Param2##Param3##Param4(Param1, Param2, Param3, Param4); \
        task->schedule(Time); \
        }

#define SCHEDULE_TASK_5(Param1, Param2, Param3, Param4, Param5, Time, Code) \
        { \
        class Param1##Param2##Param3##Param4##Param5 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param2) param2_type; \
                param2_type Param2##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param3) param3_type; \
                param3_type Param3##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param4) param4_type; \
				param4_type Param4##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param5) param5_type; \
                param5_type Param5##_p; \
		\
        public: \
                Param1##Param2##Param3##Param4##Param5(param1_type param1, param2_type param2, param3_type param3, param4_type param4, param5_type param5) : Param1##_p(param1), Param2##_p(param2), Param3##_p(param3), Param4##_p(param4), Param5##_p(param5) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Task* task = new Param1##Param2##Param3##Param4##Param5(Param1, Param2, Param3, Param4, Param5); \
        task->schedule(Time); \
        }

#define SCHEDULE_TASK_6(Param1, Param2, Param3, Param4, Param5, Param6, Time, Code) \
        { \
        class Param1##Param2##Param3##Param4##Param5##Param6 : public Task { \
                typedef BOOST_TYPEOF_TPL(Param1) param1_type; \
                param1_type Param1##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param2) param2_type; \
                param2_type Param2##_p; \
		\
                typedef BOOST_TYPEOF_TPL(Param3) param3_type; \
                param3_type Param3##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param4) param4_type; \
				param4_type Param4##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param5) param5_type; \
                param5_type Param5##_p; \
		\
				typedef BOOST_TYPEOF_TPL(Param6) param6_type; \
                param6_type Param6##_p; \
		\
        public: \
                Param1##Param2##Param3##Param4##Param5##Param6(param1_type param1, param2_type param2, param3_type param3, param4_type param4, param5_type param5, param6_type param6) : Param1##_p(param1), Param2##_p(param2), Param3##_p(param3), Param4##_p(param4), Param5##_p(param5), Param6##_p(param6) {} \
                void run() { \
                        Code; \
                } \
        }; \
        Task* task = new Param1##Param2##Param3##Param4##Param5##Param6(Param1, Param2, Param3, Param4, Param5, Param6); \
        task->schedule(Time); \
        }
#endif
