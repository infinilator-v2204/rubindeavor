#include "exception.h"
#include "generic.h"
#include "sprites.h"

#if defined(_WIN32)
#include <errhandlingapi.h>
#include <minwinbase.h>
struct {
	int code;
	char* name;
} exceptionMessageData[] = {
	{ EXCEPTION_ACCESS_VIOLATION,			"Access Violation" },
	{ EXCEPTION_DATATYPE_MISALIGNMENT,		"Datatype Misalignment" },
	{ EXCEPTION_BREAKPOINT,					"Breakpoint" },
	{ EXCEPTION_SINGLE_STEP,				"Single Step" },
	{ EXCEPTION_ARRAY_BOUNDS_EXCEEDED,		"Array Bounds Exceeded" },
	{ EXCEPTION_FLT_DENORMAL_OPERAND,		"Float Denormal Operand" },
	{ EXCEPTION_FLT_DIVIDE_BY_ZERO,			"Float Divide By Zero" },
	{ EXCEPTION_FLT_INEXACT_RESULT,			"Float Inexact Result" },
	{ EXCEPTION_FLT_INVALID_OPERATION,		"Float Invalid Operation" },
	{ EXCEPTION_FLT_OVERFLOW,				"Float Overflow" },
	{ EXCEPTION_FLT_STACK_CHECK,			"Float Stack Check" },
	{ EXCEPTION_FLT_UNDERFLOW,				"Float Underflow" },
	{ EXCEPTION_INT_DIVIDE_BY_ZERO,			"Integer Divide By Zero" },
	{ EXCEPTION_INT_OVERFLOW,				"Integer Overflow" },
	{ EXCEPTION_PRIV_INSTRUCTION,			"Privileged Instruction" },
	{ EXCEPTION_IN_PAGE_ERROR,				"In Page Error" },
	{ EXCEPTION_ILLEGAL_INSTRUCTION,		"Illegal Instruction" },
	{ EXCEPTION_NONCONTINUABLE_EXCEPTION,	"Noncontinuable Exception" },
	{ EXCEPTION_STACK_OVERFLOW,				"Stack Overflow" },
	{ EXCEPTION_INVALID_DISPOSITION,		"Invalid Disposition" },
	{ EXCEPTION_GUARD_PAGE,					"Guard Page Violation" },
	{ EXCEPTION_INVALID_HANDLE,				"Invalid Handle" },
	{ CONTROL_C_EXIT,						"Ctrl+C Exit" },
	{ 0xDEADDEAD,							"User Generated Exception" },
	{ 0xFFFFFFFF,							"Unknown Exception" },
};

long __stdcall RubindeavorExceptionHandler(PEXCEPTION_POINTERS lpExceptPtr) {
	char exceptionMessage[2048];
	
	int exceptionMessageId = 0;
	for (int i = 0; ; i++) {
		if (exceptionMessageData[i].code == 0xFFFFFFFF) {
			exceptionMessageId = i;
			break;
		}
		if (exceptionMessageData[i].code == lpExceptPtr->ExceptionRecord->ExceptionCode) {
			exceptionMessageId = i;
			break;
		}
	}
	
	#if defined(__i386__) && !defined(__x86_64)
	snprintf(exceptionMessage, 2048,
		"An exception has occurred.\n"
		"\n"
		"%s (%08lx)\n"
		"at address %p\n"
		"\n"
		"EAX: %08lX     ECX: %08lX\n"
		"EDX: %08lX     EBX: %08lX\n"
		"ESP: %08lX     EBP: %08lX\n"
		"ESI: %08lX     EDI: %08lX\n"
		"EIP: %08lX     EFlags: %08lX\n"
		"CS: %04lX DS: %04lX ES: %04lX FS: %04lX GS: %04lX SS: %04lX",
		exceptionMessageData[exceptionMessageId].name, lpExceptPtr->ExceptionRecord->ExceptionCode,
		lpExceptPtr->ExceptionRecord->ExceptionAddress,
		lpExceptPtr->ContextRecord->Eax, lpExceptPtr->ContextRecord->Ecx,
		lpExceptPtr->ContextRecord->Edx, lpExceptPtr->ContextRecord->Ebx,
		lpExceptPtr->ContextRecord->Esp, lpExceptPtr->ContextRecord->Ebp,
		lpExceptPtr->ContextRecord->Esi, lpExceptPtr->ContextRecord->Edi,
		lpExceptPtr->ContextRecord->Eip, lpExceptPtr->ContextRecord->EFlags,
		lpExceptPtr->ContextRecord->SegCs, lpExceptPtr->ContextRecord->SegDs, lpExceptPtr->ContextRecord->SegEs,
		lpExceptPtr->ContextRecord->SegFs, lpExceptPtr->ContextRecord->SegGs, lpExceptPtr->ContextRecord->SegSs
	);
	#else
	snprintf(exceptionMessage, 2048,
		"An exception has occurred.\n"
		"\n"
		"%s (%08lx)\n"
		"at address %p\n"
		"\n"
		"RAX: %016llX     RCX: %016llX\n"
		"RDX: %016llX     RBX: %016llX\n"
		"RSP: %016llX     RBP: %016llX\n"
		"RSI: %016llX     RDI: %016llX\n"
		"R8:  %016llX     R9:  %016llX\n"
		"R10: %016llX     R11: %016llX\n"
		"R12: %016llX     R13: %016llX\n"
		"R14: %016llX     R15: %016llX\n"
		"RIP: %016llX     EFlags: %08lX\n"
		"CS: %04X DS: %04X ES: %04X FS: %04X GS: %04X SS: %04X",
		exceptionMessageData[exceptionMessageId].name, lpExceptPtr->ExceptionRecord->ExceptionCode,
		lpExceptPtr->ExceptionRecord->ExceptionAddress,
		lpExceptPtr->ContextRecord->Rax, lpExceptPtr->ContextRecord->Rcx,
		lpExceptPtr->ContextRecord->Rdx, lpExceptPtr->ContextRecord->Rbx,
		lpExceptPtr->ContextRecord->Rsp, lpExceptPtr->ContextRecord->Rbp,
		lpExceptPtr->ContextRecord->Rsi, lpExceptPtr->ContextRecord->Rdi,
		lpExceptPtr->ContextRecord->R8, lpExceptPtr->ContextRecord->R9,
		lpExceptPtr->ContextRecord->R10, lpExceptPtr->ContextRecord->R11,
		lpExceptPtr->ContextRecord->R12, lpExceptPtr->ContextRecord->R13,
		lpExceptPtr->ContextRecord->R14, lpExceptPtr->ContextRecord->R15,
		lpExceptPtr->ContextRecord->Rip, lpExceptPtr->ContextRecord->EFlags,
		lpExceptPtr->ContextRecord->SegCs, lpExceptPtr->ContextRecord->SegDs, lpExceptPtr->ContextRecord->SegEs,
		lpExceptPtr->ContextRecord->SegFs, lpExceptPtr->ContextRecord->SegGs, lpExceptPtr->ContextRecord->SegSs
	);
	#endif
	
	printf("Exception occurred! Code: 0x%08lx\n", lpExceptPtr->ExceptionRecord->ExceptionCode);
	//PlaySound(SND_no);
	SetFontSprite(SPR_font_small);
	SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
	
	SetProjection(320, 240, 1);
	
	SetDrawAlpha(255);
	SetDrawColor(255, 255, 255);
	SetDrawAlpha(160);
	SetDrawColor(0, 0, 0);
	FillRect(32, 32, 576, 416);
	SetDrawAlpha(255);
	SetDrawColor(255, 255, 255);
	
	SDL_Event e;
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_WINDOWEVENT:
					switch (e.window.event) {
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							SDL_SetRenderDrawColor(globalRenderer, 0x00, 0x00, 0x00, 0xff);
							SDL_RenderClear(globalRenderer);
							break;
					}
					break;
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_ESCAPE) {
						quit = 1;
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
			}
		}
		SDL_Delay(250);
		DrawText(exceptionMessage, 2048, 44, 44, 2, 2);
		SDL_RenderPresent(globalRenderer);
	}
	return EXCEPTION_EXECUTE_HANDLER;
}
#endif
#if defined(__linux__)
#include <signal.h>
struct {
	int code;
	char* name;
} exceptionMessageData[] = {
	{ SIGHUP,				"Hangup" },
	{ SIGINT,				"Interrupt" },
	{ SIGQUIT,				"Quit" },
	{ SIGILL,				"Illegal Instruction" },
	{ SIGTRAP,				"Trace/breakpoint trap" },
	{ SIGABRT,				"Abort" },
	{ SIGBUS,				"Bus Error" },
	{ SIGFPE,				"Floating Point Exception" },
	{ SIGKILL,				"Kill" },
	{ SIGUSR1,				"User Defined Signal 1" },
	{ SIGSEGV,				"Segmentation Violation" },
	{ SIGUSR2,				"User Defined Signal 2" },
	{ SIGPIPE,				"Broken Pipe" },
	{ SIGALRM,				"Timer" },
	{ SIGTERM,				"Termination" },
	{ SIGSTKFLT,			"Stack Fault" },
	{ SIGCHLD,				"Child Stopped" },
	{ SIGCONT,				"Continue" },
	{ SIGSTOP,				"Stop" },
	{ SIGTSTP,				"Terminal Stop" },
	{ SIGTTIN,				"Terminal Input" },
	{ SIGTTOU,				"Terminal Output" },
	{ SIGURG,				"Urgent Condition" },
	{ SIGXCPU,				"CPU Time Limit" },
	{ SIGXFSZ,				"File Size Limit" },
	{ SIGVTALRM,			"Virtual Alarm Clock" },
	{ SIGPROF,				"Profiling Timer Expired" },
	{ SIGWINCH,				"Window Resize" },
	{ SIGIO,				"I/O" },
	{ SIGPWR,				"Power Failure" },
	{ SIGSYS,				"Bad System Call" },
	{ 0xFFFFFFFF,			"Unknown Exception" },
};

bool fatalErrorInProgress = false;
void RubindeavorExceptionHandler(int sig) {
	if (fatalErrorInProgress) {
		signal(sig, SIG_DFL);
		raise(sig);
		return;
	}
	fatalErrorInProgress = true;
	
	char exceptionMessage[2048];
	
	int exceptionMessageId = 0;
	for (int i = 0; ; i++) {
		if (exceptionMessageData[i].code == 0xFFFFFFFF) {
			exceptionMessageId = i;
			break;
		}
		if (exceptionMessageData[i].code == sig) {
			exceptionMessageId = i;
			break;
		}
	}
	
	snprintf(exceptionMessage, 2048,
		"An exception has occurred.\n"
		"\n"
		"%s (Signal %d)",
		exceptionMessageData[exceptionMessageId].name, sig
	);
	
	printf("Exception occurred! Code: %d\n", sig);
	SetFontSprite(SPR_font_small);
	SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
	
	SetProjection(320, 240, 1);
	
	SetDrawAlpha(255);
	SetDrawColor(255, 255, 255);
	SetDrawAlpha(160);
	SetDrawColor(0, 0, 0);
	FillRect(32, 32, 576, 416);
	SetDrawAlpha(255);
	SetDrawColor(255, 255, 255);
	
	SDL_Event e;
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_WINDOWEVENT:
					switch (e.window.event) {
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							SDL_SetRenderDrawColor(globalRenderer, 0x00, 0x00, 0x00, 0xff);
							SDL_RenderClear(globalRenderer);
							break;
					}
					break;
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_ESCAPE) {
						quit = 1;
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
			}
		}
		SDL_Delay(250);
		DrawText(exceptionMessage, 2048, 44, 44, 2, 2);
		SDL_RenderPresent(globalRenderer);
	}
	
	signal(sig, SIG_DFL);
	raise(sig);
}
#endif

void RubindeavorExceptionHandler_Enable() {
	#if defined(_WIN32)
	SetUnhandledExceptionFilter(RubindeavorExceptionHandler);
	#endif
	#if defined(__linux__)
	signal(SIGUSR1, RubindeavorExceptionHandler);
	signal(SIGUSR2, RubindeavorExceptionHandler);
	signal(SIGSEGV, RubindeavorExceptionHandler);
	signal(SIGBUS, RubindeavorExceptionHandler);
	signal(SIGILL, RubindeavorExceptionHandler);
	signal(SIGFPE, RubindeavorExceptionHandler);
	signal(SIGSYS, RubindeavorExceptionHandler);
	#endif
}
