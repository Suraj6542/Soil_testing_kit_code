//pH sensor 
if(msg.payload >=6.5 && msg.payload<=7.5)
{
    msg.payload = "Soil is having optimum pH range for optimum plant growth"

}
else if( msg.payload <= 6.5 && msg.payload>=5.5)
{
    msg.payload="slightly acidic"
}
else if(msg.payload<5.5 && msg.payload>=5.0)
{
    msg.payload ="Moderately acidic"
}
else if(msg.payload <5.0 && msg.payload >= 4.5)
{
    msg.payload = "Strongly acidic"
}
else if(msg.payload<4.5)
{
    msg.payload= "Extremely acidic"
}
else if(msg.payload>7.5 && msg.payload<=8.0)
{
    msg.payload = "Slightly alkanine"
}
else if(msg.payloadd >8.0 && msg.payload<= 8.5)
{
    msg.payload = "Medium alkanine"
}
else 
{
    msg.payload = "Strongly alkaline"
}
return msg;