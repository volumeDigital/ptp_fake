#include <linux/init.h>
#include <linux/module.h>
#include <linux/ptp_clock_kernel.h>
#include <linux/math64.h>

/** PTP FAKE
  * 
  * A simple, fake PTP clock that never advances.
  *
  * Implemented:
  *     adjtime
  *     gettime
  *     settime
  */

struct ptp_fake {
    const char              *name;
    struct ptp_clock        *clock;
    struct ptp_clock_info   clock_info;
    struct timespec         current_time;
};

static int ptp_fake_adjfreq(struct ptp_clock_info *ptp, s32 delta)
{
    return -EOPNOTSUPP;
}

static int ptp_fake_adjtime(struct ptp_clock_info *ptp, s64 delta)
{
    struct ptp_fake *fake = container_of(ptp, struct ptp_fake, clock_info);
    timespec_add_ns(&(fake->current_time), delta);
    return 0;
}

static int ptp_fake_gettime(struct ptp_clock_info *ptp, struct timespec *ts)
{
    struct ptp_fake *fake = container_of(ptp, struct ptp_fake, clock_info);
    *ts = fake->current_time;
    return 0;
}

static int ptp_fake_settime(struct ptp_clock_info *ptp, const struct timespec *ts)
{
    struct ptp_fake *fake = container_of(ptp, struct ptp_fake, clock_info);
    fake->current_time = *ts;
    return 0;
}

static int ptp_fake_enable(struct ptp_clock_info *ptp,
              struct ptp_clock_request *request, int on)
{
    return -EOPNOTSUPP;
}

static struct ptp_clock_info clock_info= {
    .owner      = THIS_MODULE,
    .name       = "Fake PTP Clock",
    .max_adj    = 0,    /* No adjustment */
    .n_ext_ts   = 0,    /* No external timestamp channels */
    .pps        = 0,    /* No periodic signals */
    .adjfreq    = ptp_fake_adjfreq,
    .adjtime    = ptp_fake_adjtime,
    .gettime    = ptp_fake_gettime,
    .settime    = ptp_fake_settime,
    .enable     = ptp_fake_enable,
};

static struct ptp_fake global_fake;

static int ptp_fake_init(void)
{
    printk("Fake PTP Clock Init\n");
    global_fake.clock_info  = clock_info;
    global_fake.clock       = ptp_clock_register(&(global_fake.clock_info));
    return 0;
}

static void ptp_fake_exit(void)
{
    printk("Fake PTP Clock Exit\n");
    ptp_clock_unregister(global_fake.clock);
}

module_init(ptp_fake_init);
module_exit(ptp_fake_exit);

MODULE_AUTHOR("Tim Cussins <timcussins@eml.cc>");
MODULE_DESCRIPTION("Fake PTP Clock");
MODULE_LICENSE("Dual BSD/GPL");

