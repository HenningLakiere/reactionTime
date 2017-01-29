#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x2ff4de1e, "module_layout" },
	{ 0x4e115791, "xnintr_detach" },
	{ 0xf10ef398, "xnintr_disable" },
	{ 0xb5877ff0, "xnintr_enable" },
	{ 0x2c6aa31e, "rtdm_task_init" },
	{ 0x80f042f5, "rtdm_irq_request" },
	{ 0xbc477a2, "irq_set_irq_type" },
	{ 0xfe990052, "gpio_free" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x11f447ce, "__gpio_to_irq" },
	{ 0x98ed842a, "__rtdm_task_sleep" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0x12d6db8a, "rtdm_tbase" },
	{ 0xd6fe3c66, "xnarch_get_cpu_time" },
	{ 0x27e1a049, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

