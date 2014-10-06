#include <linux/init.h>
#include <linux/module.h>
#include <linux/ptp_clock_kernel.h>
MODULE_LICENSE("Dual BSD/GPL");

static int ptp_fake_init(void)
{
    printk("Fake PTP Clock Init\n");
    return 0;
}

static void ptp_fake_exit(void)
{
    printk("Fake PTP Clock Exit\n");
}

module_init(ptp_fake_init);
module_exit(ptp_fake_exit);

int ptp_fake_adjfreq(struct ptp_clock_info *ptp, s32 delta)
{
    return -EOPNOTSUPP;
}

int ptp_fake_adjtime(struct ptp_clock_info *ptp, s64 delta)
{
    return -EOPNOTSUPP;
}

int ptp_fake_gettime(struct ptp_clock_info *ptp, struct timespec *ts)
{
    return -EOPNOTSUPP;
}

int ptp_fake_settime(struct ptp_clock_info *ptp, const struct timespec *ts)
{
    return -EOPNOTSUPP;
}

int ptp_fake_enable(struct ptp_clock_info *ptp,
              struct ptp_clock_request *request, int on)
{
    return -EOPNOTSUPP;
}

