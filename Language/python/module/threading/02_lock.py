import urllib2
import threading

# list 1 of urls to fetch
urls1 = ['https://www.yahoo.com', 'https://www.yahoo.com']
# list 2 of urls to fetch
urls2 = ['https://www.yahoo.com', 'https://www.yahoo.com']


class FetchUrls(threading.Thread):
    """
    Thread checking URLs.
    """

    def __init__(self, urls, output, lock):
        """
        Constructor.

        @param urls list of urls to check
        @param output file to write urls output
        """
        threading.Thread.__init__(self)
        self.urls = urls
        self.output = output
        self.lock = lock

    def run(self):
        """
        Thread run method. Check URLs one by one.
        """
        while self.urls:
            url = self.urls.pop()
            req = urllib2.Request(url)
            try:
                d = urllib2.urlopen(req)
            except urllib2.URLError, e:
                print 'URL %s failed: %s' % (url, e.reason)

            self.lock.acquire()
            print 'lock acquired by %s' % self.name
            self.output.write(d.read())
            print 'write done by %s' % self.name
            print 'lock released by %s' % self.name
            print 'URL %s fetched by %s' % (url, self.name)
            self.lock.release()

            # with self.lock:
            #     print 'lock acquired by %s' % self.name
            #     self.output.write(d.read())
            #     print 'write done by %s' % self.name
            #     print 'lock released by %s' % self.name
            #     print 'URL %s fetched by %s' % (url, self.name)


def main():
    lock = threading.Lock()
    f = open('output.txt', 'w+')
    t1 = FetchUrls(urls1, f, lock)
    t2 = FetchUrls(urls2, f, lock)
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    f.close()


if __name__ == '__main__':
    main()
