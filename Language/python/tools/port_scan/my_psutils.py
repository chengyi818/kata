import psutil

AF_INET = 2


def get_netcard(netcard_list):
    netcard_info = []
    info = psutil.net_if_addrs()
    for k, v in info.items():
        # print("k = {0}, v = {1}".format(k, v))
        for item in v:
            # 过滤非Ipv4
            if not item[0] == AF_INET:
                continue
            # 过滤本地地址
            if item[1] == '127.0.0.1':
                continue
            # 过滤down的网卡
            if k not in netcard_list:
                continue
            # 过滤子网掩码小于20的网卡
            if item[2] < "255.255.240.0":
                continue

            netcard_info.append((k, item[1], item[2]))

    return netcard_info


# 过滤掉isup为False的网卡
def get_invalid_net_card():
    temp_list = list()
    info = psutil.net_if_stats()
    for k, v in info.items():
        # print("k = {0}, v = {1}".format(k, v))
        if v[0]:
            temp_list.append(k)
    return temp_list


if __name__ == '__main__':
    netcard_list = get_invalid_net_card()

    for item in get_netcard(netcard_list):
        print(item)
