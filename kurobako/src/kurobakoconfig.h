#ifndef KUROBAKOCONFIG_H
#define KUROBAKOCONFIG_H

#define KUROBAKO_VERSION_MAJOR 0
#define KUROBAKO_VERSION_MINOR 1

#ifdef KUROBAKO_Debug
#define KBK_DEBUG
#elif KUROBAKO_Relase
#define KBK_RELEASE
#elif KUROBAKO_Profile
#define KBK_PROFILE
#elif KUROBAKO_Final
#define KBK_FINAL
#endif

#if defined(KBK_DEBUG) || defined(KBK_RELEASE) || defined(KBK_PROFILE)
#define KBK_MEMTAG
#endif


#endif
