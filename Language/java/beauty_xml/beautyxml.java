/**
 * Created by chengyi on 7/6/16.
 */

import javax.xml.transform.TransformerException;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import java.io.StringReader;
import java.io.StringWriter;

public class beautyxml {

    public static String beautyXml(String unformattedXml) {
        Source xmlInput = new StreamSource(new StringReader(unformattedXml));
        StringWriter stringWriter = new StringWriter();
        try {
            TransformerFactory transformerFactory = TransformerFactory.newInstance();

            Transformer transformer = transformerFactory.newTransformer();
            transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            transformer.transform(xmlInput, new StreamResult(stringWriter));

            String pretty = stringWriter.toString();
            return pretty;
        } catch (TransformerException e) {
            return unformattedXml;
        }
    }
}
