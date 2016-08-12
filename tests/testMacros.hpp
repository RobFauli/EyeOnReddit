#ifndef PHYSICSSANDBOX_TESTMACROS_HPP
#define PHYSICSSANDBOX_TESTMACROS_HPP

#define SETUP_Q_CORE_APP char *cargv = new char [1]; \
                         int i = 1; \
                         QCoreApplication test(i, &cargv);
#endif //PHYSICSSANDBOX_TESTMACROS_HPP
