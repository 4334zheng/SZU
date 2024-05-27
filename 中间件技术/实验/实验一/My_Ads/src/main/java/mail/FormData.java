package mail;
import lombok.Data;
import java.util.*;
@Data
public class FormData {
    public String name;
    public String value;
    public String contentType;
    public byte[] file;
}
