#ifndef LIB_linkingFcc_GLOBAL_H
#define LIB_linkingFcc_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIB_linkingFcc_LIBRARY)
#  define LIB_linkingFccSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIB_linkingFccSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIB_linkingFcc_GLOBAL_H
