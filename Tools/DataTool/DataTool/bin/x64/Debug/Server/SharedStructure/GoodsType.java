package snowpipe.common.protocol.generated.sharedStructure;
import java.util.HashMap;
import java.util.Map;
import snowpipe.common.*;

public enum GoodsType implements IntegerEnum
{
	None(0,""),
	Cash(1,"캐쉬"),
	PartsPoint(2,"나사"),
	FoodPoint(3,"음식"),
	MedalPoint(5,"메달"),
	Bill(6,"현금재화(서버 사용)"),
	WoodPoint(7,"목재"),
	GasolinePoint(8,"가솔린"),
	;

private static final Map<Integer, GoodsType> VALUE_AND_TYPE_MAP = new HashMap<>();
static { for(GoodsType type:values()) { VALUE_AND_TYPE_MAP.put(type.getValue(), type); } }
private int value;
private String name;
private String description;
private GoodsType(int typeValue, String description) { this.value = typeValue; this.description = description; this.name = this.toString();}
public int getValue() { return value; }
public String getName() { return name; }
public String getDescription() { return description; }
public static GoodsType valueOf(int typeValue) { if(!VALUE_AND_TYPE_MAP.containsKey(typeValue)) { throw new RuntimeException("invalid typeValue: " + typeValue); } return VALUE_AND_TYPE_MAP.get(typeValue); }
}

