#pragma once

#include <QtCore/qglobal.h>

#if defined(ALGORITHMSMODULE_LIBRARY)
#  define ALGORITHMSMODULE_EXPORT Q_DECL_EXPORT
#else
#  define ALGORITHMSMODULE_EXPORT Q_DECL_IMPORT
#endif
