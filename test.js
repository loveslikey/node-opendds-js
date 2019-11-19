const addon = require('bindings')('opendds')

async function _main() {
    const factory = await addon.init('-DCPSInfoRepo', '127.0.0.1:12345')
    const participant = await factory.create_participant(DOMAIN_ID, qos)
    //dds_inf = 0x7fffffff,
    const infinite = {sec: addon.dds_inf, nanosec: addon.dds_inf}
    
}

_main()