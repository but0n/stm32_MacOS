#include <avm_core.h>

int main() {

	avm_core_module_st.init_module(NULL);

	while(1) {
		uart_sendStr("Hello World!\r\n");
	}
}
