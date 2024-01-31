import yaml

with open('data/test_list.yaml', encoding='utf-8') as file1:
    data = yaml.load_all(file1, Loader=yaml.FullLoader)  # 读取yaml文件
    for data_ in data:
        print(data_)

        sorted = yaml.dump(data_, sort_keys=True)
        print(sorted)
