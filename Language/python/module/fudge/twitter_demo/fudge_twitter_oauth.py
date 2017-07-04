#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 04 Jul 2017 11:09:47 AM CST

import fudge
from twitter_oauth_demo import post_msg_to_twitter


@fudge.patch('twitter_oauth.GetOauth', 'twitter_oauth.Api')
def test_post_msg_to_twitter(msg, FakeGetOauth, FakeApi):
    FakeGetOauth.expects_call() \
        .with_args('***', '***')

    FakeApi.expects_call() \
        .with_args('***', '***', '***', '***') \
        .returns_fake() \
        .expects('post_update').with_args(u'Hello, Twitter:okey')

    post_msg_to_twitter(msg)


if __name__ == '__main__':
    test_post_msg_to_twitter('okey')
