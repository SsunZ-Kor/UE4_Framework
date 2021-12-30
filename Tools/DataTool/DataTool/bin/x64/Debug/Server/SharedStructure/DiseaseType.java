package snowpipe.common.protocol.generated.sharedStructure;
import java.util.HashMap;
import java.util.Map;
import snowpipe.common.*;

public enum DiseaseType implements IntegerEnum
{
	None(0,""),
	SlightInjury(1,""),
	SeriousInjury(2,""),
	Moribund(3,""),
	;

private static final Map<Integer, DiseaseType> VALUE_AND_TYPE_MAP = new HashMap<>();
static { for(DiseaseType type:values()) { VALUE_AND_TYPE_MAP.put(type.getValue(), type); } }
private int value;
private String name;
private String description;
private DiseaseType(int typeValue, String description) { this.value = typeValue; this.description = description; this.name = this.toString();}
public int getValue() { return value; }
public String getName() { return name; }
public String getDescription() { return description; }
public static DiseaseType valueOf(int typeValue) { if(!VALUE_AND_TYPE_MAP.containsKey(typeValue)) { throw new RuntimeException("invalid typeValue: " + typeValue); } return VALUE_AND_TYPE_MAP.get(typeValue); }
}

