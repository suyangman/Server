#pragma once

#define VERIFY(expr) if(!expr){\
				exit(EXIT_FAILURE);\
				}\

#define CtlFD(int epoll, int fd, int op, unsigned int mask, void* pv) epoll_event evt = { mask, pv };\
	int i_res = epoll_ctl(epoll, op, fd, &evt);\

#define	DelFD(int epoll, int fd) CtlFD(epoll, fd, EPOLL_CTL_DEL, 0, nullptr);\

#define AddFD(int epoll, int fd, unsigned int mask, void* pv) CtlFD(epoll, fd, EPOLL_CTL_ADD, mask, pv);\

#define ModFD(int epoll, int fd, unsigned int mask, void* pv) CtlFD(epoll, fd, EPOLL_CTL_MOD, mask, pv);\