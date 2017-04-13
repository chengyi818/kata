import sun.rmi.runtime.Log;


public class Main {

    public static void main(String[] args) {

        String xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><root><test><item0>a</item0><item1>b</item1></test></root>";


        String str = beautyxml.beautyXml(xml);
        System.out.println(str);


    }

}
