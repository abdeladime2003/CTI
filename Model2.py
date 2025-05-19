{
 "cells": [
  {
   "cell_type": "code",
   "execution_count": null,
   "id": "2db074aa",
   "metadata": {},
   "outputs": [
    {
     "name": "stderr",
     "output_type": "stream",
     "text": [
      "                                                                                \r"
     ]
    },
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "Raw data preview:\n",
      "+------+------+-----------------------------------------------------------------------+--------+-------------+---------------------------------------------------------------------------------------------------+--------------------------------+---------------------------+--------+--------------+-------------------------------------------+------------+----------+------+-------+--------------+------------------------------------------------------------------------------------------------------------------------------+\n",
      "|_c0   |_c1   |_c2                                                                    |_c3     |_c4          |_c5                                                                                                |_c6                             |_c7                        |_c8     |_c9           |_c10                                       |_c11        |_c12      |_c13  |_c14   |_c15          |_c16                                                                                                                          |\n",
      "+------+------+-----------------------------------------------------------------------+--------+-------------+---------------------------------------------------------------------------------------------------+--------------------------------+---------------------------+--------+--------------+-------------------------------------------+------------+----------+------+-------+--------------+------------------------------------------------------------------------------------------------------------------------------+\n",
      "|null  |Method|User-Agent                                                             |Pragma  |Cache-Control|Accept                                                                                             |Accept-encoding                 |Accept-charset             |language|host          |cookie                                     |content-type|connection|lenght|content|classification|URL                                                                                                                           |\n",
      "|Normal|GET   |Mozilla/5.0 (compatible; Konqueror/3.5; Linux) KHTML/3.5.8 (like Gecko)|no-cache|no-cache     |text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5|x-gzip, x-deflate, gzip, deflate|utf-8, utf-8;q=0.5, *;q=0.5|en      |localhost:8080|JSESSIONID=1F767F17239C9B670A39E9B10C3825F4|null        |close     |null  |null   |0             |http://localhost:8080/tienda1/index.jsp HTTP/1.1                                                                              |\n",
      "|Normal|GET   |Mozilla/5.0 (compatible; Konqueror/3.5; Linux) KHTML/3.5.8 (like Gecko)|no-cache|no-cache     |text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5|x-gzip, x-deflate, gzip, deflate|utf-8, utf-8;q=0.5, *;q=0.5|en      |localhost:8080|JSESSIONID=81761ACA043B0E6014CA42A4BCD06AB5|null        |close     |null  |null   |0             |http://localhost:8080/tienda1/publico/anadir.jsp?id=3&nombre=Vino+Rioja&precio=100&cantidad=55&B1=A%F1adir+al+carrito HTTP/1.1|\n",
      "+------+------+-----------------------------------------------------------------------+--------+-------------+---------------------------------------------------------------------------------------------------+--------------------------------+---------------------------+--------+--------------+-------------------------------------------+------------+----------+------+-------+--------------+------------------------------------------------------------------------------------------------------------------------------+\n",
      "only showing top 3 rows\n",
      "\n"
     ]
    },
    {
     "name": "stderr",
     "output_type": "stream",
     "text": [
      "                                                                                \r"
     ]
    },
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "Number of records: 61066\n",
      "\n",
      "Label distribution:\n"
     ]
    },
    {
     "name": "stderr",
     "output_type": "stream",
     "text": [
      "                                                                                \r"
     ]
    },
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "+-----+-----+\n",
      "|label|count|\n",
      "+-----+-----+\n",
      "|    1|25066|\n",
      "|    0|36000|\n",
      "+-----+-----+\n",
      "\n",
      "\n",
      "Checking for null values in important columns:\n"
     ]
    },
    {
     "name": "stderr",
     "output_type": "stream",
     "text": [
      "                                                                                \r"
     ]
    },
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "+-------+------+----------+------+-------------+------+---------------+--------------+--------+----+------+------------+----------+------+-------+--------------+---+------------------+-----+\n",
      "|Unnamed|Method|User-Agent|Pragma|Cache-Control|Accept|Accept-encoding|Accept-charset|language|host|cookie|content-type|connection|length|content|classification|URL|classification_int|label|\n",
      "+-------+------+----------+------+-------------+------+---------------+--------------+--------+----+------+------------+----------+------+-------+--------------+---+------------------+-----+\n",
      "|1      |0     |0         |0     |0            |397   |0              |0             |0       |0   |0     |43088       |0         |43088 |43088  |0             |0  |0                 |0    |\n",
      "+-------+------+----------+------+-------------+------+---------------+--------------+--------+----+------+------------+----------+------+-------+--------------+---+------------------+-----+\n",
      "\n",
      "\n",
      "Removed header row.\n",
      "\n",
      "Derived features preview:\n",
      "+----------+-----------+-------+----------------+-----------------------+-----+\n",
      "|url_length|has_content|is_post|has_query_params|sql_injection_indicator|label|\n",
      "+----------+-----------+-------+----------------+-----------------------+-----+\n",
      "|        48|          1|      0|               0|                      0|    0|\n",
      "|       126|          1|      0|               1|                      0|    0|\n",
      "|        57|          1|      1|               0|                      0|    0|\n",
      "|       125|          1|      0|               1|                      0|    0|\n",
      "|        61|          1|      1|               0|                      0|    0|\n",
      "+----------+-----------+-------+----------------+-----------------------+-----+\n",
      "only showing top 5 rows\n",
      "\n",
      "\n",
      "After filtering null labels: 61065 rows\n",
      "\n",
      "Using numerical features: ['url_length', 'has_content', 'is_post', 'has_query_params', 'sql_injection_indicator']\n",
      "\n",
      "Splitting data into training and test sets...\n"
     ]
    },
    {
     "name": "stderr",
     "output_type": "stream",
     "text": [
      "                                                                                \r"
     ]
    },
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "Training data: 49091 examples\n"
     ]
    },
    {
     "name": "stderr",
     "output_type": "stream",
     "text": [
      "ERROR:root:Exception while sending command.                         (1 + 7) / 8]\n",
      "Traceback (most recent call last):\n",
      "  File \"/home/abdo/Cti_Project/myenv/lib/python3.12/site-packages/py4j/clientserver.py\", line 516, in send_command\n",
      "    raise Py4JNetworkError(\"Answer from Java side is empty\")\n",
      "py4j.protocol.Py4JNetworkError: Answer from Java side is empty\n",
      "\n",
      "During handling of the above exception, another exception occurred:\n",
      "\n",
      "Traceback (most recent call last):\n",
      "  File \"/home/abdo/Cti_Project/myenv/lib/python3.12/site-packages/py4j/java_gateway.py\", line 1038, in send_command\n",
      "    response = connection.send_command(command)\n",
      "               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n",
      "  File \"/home/abdo/Cti_Project/myenv/lib/python3.12/site-packages/py4j/clientserver.py\", line 539, in send_command\n",
      "    raise Py4JNetworkError(\n",
      "py4j.protocol.Py4JNetworkError: Error while sending or receiving\n"
     ]
    },
    {
     "ename": "Py4JError",
     "evalue": "An error occurred while calling o481.count",
     "output_type": "error",
     "traceback": [
      "\u001b[0;31m---------------------------------------------------------------------------\u001b[0m",
      "\u001b[0;31mPy4JError\u001b[0m                                 Traceback (most recent call last)",
      "Cell \u001b[0;32mIn[2], line 165\u001b[0m\n\u001b[1;32m    163\u001b[0m train_data, test_data \u001b[38;5;241m=\u001b[39m df\u001b[38;5;241m.\u001b[39mrandomSplit([\u001b[38;5;241m0.8\u001b[39m, \u001b[38;5;241m0.2\u001b[39m], seed\u001b[38;5;241m=\u001b[39m\u001b[38;5;241m42\u001b[39m)\n\u001b[1;32m    164\u001b[0m \u001b[38;5;28mprint\u001b[39m(\u001b[38;5;124mf\u001b[39m\u001b[38;5;124m\"\u001b[39m\u001b[38;5;124mTraining data: \u001b[39m\u001b[38;5;132;01m{\u001b[39;00mtrain_data\u001b[38;5;241m.\u001b[39mcount()\u001b[38;5;132;01m}\u001b[39;00m\u001b[38;5;124m examples\u001b[39m\u001b[38;5;124m\"\u001b[39m)\n\u001b[0;32m--> 165\u001b[0m \u001b[38;5;28mprint\u001b[39m(\u001b[38;5;124mf\u001b[39m\u001b[38;5;124m\"\u001b[39m\u001b[38;5;124mTest data: \u001b[39m\u001b[38;5;132;01m{\u001b[39;00m\u001b[43mtest_data\u001b[49m\u001b[38;5;241;43m.\u001b[39;49m\u001b[43mcount\u001b[49m\u001b[43m(\u001b[49m\u001b[43m)\u001b[49m\u001b[38;5;132;01m}\u001b[39;00m\u001b[38;5;124m examples\u001b[39m\u001b[38;5;124m\"\u001b[39m)\n\u001b[1;32m    167\u001b[0m \u001b[38;5;66;03m# 15. Train the model with error handling\u001b[39;00m\n\u001b[1;32m    168\u001b[0m \u001b[38;5;28;01mtry\u001b[39;00m:\n",
      "File \u001b[0;32m~/Cti_Project/myenv/lib/python3.12/site-packages/pyspark/sql/dataframe.py:1193\u001b[0m, in \u001b[0;36mDataFrame.count\u001b[0;34m(self)\u001b[0m\n\u001b[1;32m   1170\u001b[0m \u001b[38;5;28;01mdef\u001b[39;00m\u001b[38;5;250m \u001b[39m\u001b[38;5;21mcount\u001b[39m(\u001b[38;5;28mself\u001b[39m) \u001b[38;5;241m-\u001b[39m\u001b[38;5;241m>\u001b[39m \u001b[38;5;28mint\u001b[39m:\n\u001b[1;32m   1171\u001b[0m \u001b[38;5;250m    \u001b[39m\u001b[38;5;124;03m\"\"\"Returns the number of rows in this :class:`DataFrame`.\u001b[39;00m\n\u001b[1;32m   1172\u001b[0m \n\u001b[1;32m   1173\u001b[0m \u001b[38;5;124;03m    .. versionadded:: 1.3.0\u001b[39;00m\n\u001b[0;32m   (...)\u001b[0m\n\u001b[1;32m   1191\u001b[0m \u001b[38;5;124;03m    3\u001b[39;00m\n\u001b[1;32m   1192\u001b[0m \u001b[38;5;124;03m    \"\"\"\u001b[39;00m\n\u001b[0;32m-> 1193\u001b[0m     \u001b[38;5;28;01mreturn\u001b[39;00m \u001b[38;5;28mint\u001b[39m(\u001b[38;5;28;43mself\u001b[39;49m\u001b[38;5;241;43m.\u001b[39;49m\u001b[43m_jdf\u001b[49m\u001b[38;5;241;43m.\u001b[39;49m\u001b[43mcount\u001b[49m\u001b[43m(\u001b[49m\u001b[43m)\u001b[49m)\n",
      "File \u001b[0;32m~/Cti_Project/myenv/lib/python3.12/site-packages/py4j/java_gateway.py:1322\u001b[0m, in \u001b[0;36mJavaMember.__call__\u001b[0;34m(self, *args)\u001b[0m\n\u001b[1;32m   1316\u001b[0m command \u001b[38;5;241m=\u001b[39m proto\u001b[38;5;241m.\u001b[39mCALL_COMMAND_NAME \u001b[38;5;241m+\u001b[39m\\\n\u001b[1;32m   1317\u001b[0m     \u001b[38;5;28mself\u001b[39m\u001b[38;5;241m.\u001b[39mcommand_header \u001b[38;5;241m+\u001b[39m\\\n\u001b[1;32m   1318\u001b[0m     args_command \u001b[38;5;241m+\u001b[39m\\\n\u001b[1;32m   1319\u001b[0m     proto\u001b[38;5;241m.\u001b[39mEND_COMMAND_PART\n\u001b[1;32m   1321\u001b[0m answer \u001b[38;5;241m=\u001b[39m \u001b[38;5;28mself\u001b[39m\u001b[38;5;241m.\u001b[39mgateway_client\u001b[38;5;241m.\u001b[39msend_command(command)\n\u001b[0;32m-> 1322\u001b[0m return_value \u001b[38;5;241m=\u001b[39m \u001b[43mget_return_value\u001b[49m\u001b[43m(\u001b[49m\n\u001b[1;32m   1323\u001b[0m \u001b[43m    \u001b[49m\u001b[43manswer\u001b[49m\u001b[43m,\u001b[49m\u001b[43m \u001b[49m\u001b[38;5;28;43mself\u001b[39;49m\u001b[38;5;241;43m.\u001b[39;49m\u001b[43mgateway_client\u001b[49m\u001b[43m,\u001b[49m\u001b[43m \u001b[49m\u001b[38;5;28;43mself\u001b[39;49m\u001b[38;5;241;43m.\u001b[39;49m\u001b[43mtarget_id\u001b[49m\u001b[43m,\u001b[49m\u001b[43m \u001b[49m\u001b[38;5;28;43mself\u001b[39;49m\u001b[38;5;241;43m.\u001b[39;49m\u001b[43mname\u001b[49m\u001b[43m)\u001b[49m\n\u001b[1;32m   1325\u001b[0m \u001b[38;5;28;01mfor\u001b[39;00m temp_arg \u001b[38;5;129;01min\u001b[39;00m temp_args:\n\u001b[1;32m   1326\u001b[0m     \u001b[38;5;28;01mif\u001b[39;00m \u001b[38;5;28mhasattr\u001b[39m(temp_arg, \u001b[38;5;124m\"\u001b[39m\u001b[38;5;124m_detach\u001b[39m\u001b[38;5;124m\"\u001b[39m):\n",
      "File \u001b[0;32m~/Cti_Project/myenv/lib/python3.12/site-packages/pyspark/errors/exceptions/captured.py:169\u001b[0m, in \u001b[0;36mcapture_sql_exception.<locals>.deco\u001b[0;34m(*a, **kw)\u001b[0m\n\u001b[1;32m    167\u001b[0m \u001b[38;5;28;01mdef\u001b[39;00m\u001b[38;5;250m \u001b[39m\u001b[38;5;21mdeco\u001b[39m(\u001b[38;5;241m*\u001b[39ma: Any, \u001b[38;5;241m*\u001b[39m\u001b[38;5;241m*\u001b[39mkw: Any) \u001b[38;5;241m-\u001b[39m\u001b[38;5;241m>\u001b[39m Any:\n\u001b[1;32m    168\u001b[0m     \u001b[38;5;28;01mtry\u001b[39;00m:\n\u001b[0;32m--> 169\u001b[0m         \u001b[38;5;28;01mreturn\u001b[39;00m \u001b[43mf\u001b[49m\u001b[43m(\u001b[49m\u001b[38;5;241;43m*\u001b[39;49m\u001b[43ma\u001b[49m\u001b[43m,\u001b[49m\u001b[43m \u001b[49m\u001b[38;5;241;43m*\u001b[39;49m\u001b[38;5;241;43m*\u001b[39;49m\u001b[43mkw\u001b[49m\u001b[43m)\u001b[49m\n\u001b[1;32m    170\u001b[0m     \u001b[38;5;28;01mexcept\u001b[39;00m Py4JJavaError \u001b[38;5;28;01mas\u001b[39;00m e:\n\u001b[1;32m    171\u001b[0m         converted \u001b[38;5;241m=\u001b[39m convert_exception(e\u001b[38;5;241m.\u001b[39mjava_exception)\n",
      "File \u001b[0;32m~/Cti_Project/myenv/lib/python3.12/site-packages/py4j/protocol.py:334\u001b[0m, in \u001b[0;36mget_return_value\u001b[0;34m(answer, gateway_client, target_id, name)\u001b[0m\n\u001b[1;32m    330\u001b[0m             \u001b[38;5;28;01mraise\u001b[39;00m Py4JError(\n\u001b[1;32m    331\u001b[0m                 \u001b[38;5;124m\"\u001b[39m\u001b[38;5;124mAn error occurred while calling \u001b[39m\u001b[38;5;132;01m{0}\u001b[39;00m\u001b[38;5;132;01m{1}\u001b[39;00m\u001b[38;5;132;01m{2}\u001b[39;00m\u001b[38;5;124m. Trace:\u001b[39m\u001b[38;5;130;01m\\n\u001b[39;00m\u001b[38;5;132;01m{3}\u001b[39;00m\u001b[38;5;130;01m\\n\u001b[39;00m\u001b[38;5;124m\"\u001b[39m\u001b[38;5;241m.\u001b[39m\n\u001b[1;32m    332\u001b[0m                 \u001b[38;5;28mformat\u001b[39m(target_id, \u001b[38;5;124m\"\u001b[39m\u001b[38;5;124m.\u001b[39m\u001b[38;5;124m\"\u001b[39m, name, value))\n\u001b[1;32m    333\u001b[0m     \u001b[38;5;28;01melse\u001b[39;00m:\n\u001b[0;32m--> 334\u001b[0m         \u001b[38;5;28;01mraise\u001b[39;00m Py4JError(\n\u001b[1;32m    335\u001b[0m             \u001b[38;5;124m\"\u001b[39m\u001b[38;5;124mAn error occurred while calling \u001b[39m\u001b[38;5;132;01m{0}\u001b[39;00m\u001b[38;5;132;01m{1}\u001b[39;00m\u001b[38;5;132;01m{2}\u001b[39;00m\u001b[38;5;124m\"\u001b[39m\u001b[38;5;241m.\u001b[39m\n\u001b[1;32m    336\u001b[0m             \u001b[38;5;28mformat\u001b[39m(target_id, \u001b[38;5;124m\"\u001b[39m\u001b[38;5;124m.\u001b[39m\u001b[38;5;124m\"\u001b[39m, name))\n\u001b[1;32m    337\u001b[0m \u001b[38;5;28;01melse\u001b[39;00m:\n\u001b[1;32m    338\u001b[0m     \u001b[38;5;28mtype\u001b[39m \u001b[38;5;241m=\u001b[39m answer[\u001b[38;5;241m1\u001b[39m]\n",
      "\u001b[0;31mPy4JError\u001b[0m: An error occurred while calling o481.count"
     ]
    },
    {
     "name": "stderr",
     "output_type": "stream",
     "text": [
      "ERROR:root:Exception while sending command.\n",
      "Traceback (most recent call last):\n",
      "  File \"/home/abdo/Cti_Project/myenv/lib/python3.12/site-packages/py4j/clientserver.py\", line 516, in send_command\n",
      "    raise Py4JNetworkError(\"Answer from Java side is empty\")\n",
      "py4j.protocol.Py4JNetworkError: Answer from Java side is empty\n",
      "\n",
      "During handling of the above exception, another exception occurred:\n",
      "\n",
      "Traceback (most recent call last):\n",
      "  File \"/home/abdo/Cti_Project/myenv/lib/python3.12/site-packages/py4j/java_gateway.py\", line 1038, in send_command\n",
      "    response = connection.send_command(command)\n",
      "               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n",
      "  File \"/home/abdo/Cti_Project/myenv/lib/python3.12/site-packages/py4j/clientserver.py\", line 539, in send_command\n",
      "    raise Py4JNetworkError(\n",
      "py4j.protocol.Py4JNetworkError: Error while sending or receiving\n"
     ]
    }
   ],
   "source": []
  }
 ],
 "metadata": {
  "kernelspec": {
   "display_name": "myenv",
   "language": "python",
   "name": "python3"
  },
  "language_info": {
   "codemirror_mode": {
    "name": "ipython",
    "version": 3
   },
   "file_extension": ".py",
   "mimetype": "text/x-python",
   "name": "python",
   "nbconvert_exporter": "python",
   "pygments_lexer": "ipython3",
   "version": "3.12.3"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 5
}
