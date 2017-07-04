#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 04 Jul 2017 11:04:31 AM CST
import twitter_oauth   # pip install twitter_oauth


consumer_key = '***'
consumer_secret = '***'
oauth_token = "***"
oauth_token_secret = '***'


def post_msg_to_twitter(msg):
    # create GetOauth instance
    get_oauth_obj = twitter_oauth.GetOauth(consumer_key, consumer_secret)

    # create Api instance
    api = twitter_oauth.Api(consumer_key, consumer_secret,
                            oauth_token, oauth_token_secret)

    # post update
    api.post_update(u'Hello, Twitter:' + msg)

    print("send:%s" % msg)
