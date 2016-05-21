

# Introduction:

  grpc_oc_decoder.py is used to fulfil grpc connection to the DUT, setup grpc tunnel and decode then write the data to log files.
  Later improvment will write the decoded jvision sensor data into database.
  
  For detailed grpc/oc definition, please refer to up-to-date 
  [agent.proto](https://github.com/nkumar43212/jvsim/blob/master/protos/agent.proto) 

  Contact: wtang@juniper.net

# Python enviorment requirement:
  > pip freeze

  make sure:
  * grpcio version > 0.13.0
  * protobuf version > 3.0.0

# Usage:
  > python grpc_oc_decoder.py -c config.json

# log path:
  * ./jvision_log/[log_head]_nodeName_threadID.txt
  e.g. grpc.session_hanoi_1.txt, grpc.data_hanoi_1.txt

# Config file guideline:
  The config.json is a json formatted file for customizing grpc APIs.
  * The json file uses key/value pair, i.e. key:value


    ## Subscribe to a sensor report
    ## subs.json:
    ```
       {
        "dut_list": // Top level is dut_list composed of a list of DUT
               [
                 {
                   "ip": "hanoi",   //DUT IP address or name of the DUT
                   "port":50051,    //grpc port should be always 50051
                   "session_log":"grpc.session",    //Grpc session_log name
                   "log_file":"grpc.data", //grpc data log header
                   "oc_rpc" : ["subscribe"], //which RPC to call, subscribe in this case
                   "subscribe": {
                                  "path_list": [{ "path":"/junos/system/linecard/optics/", "filter":"", "sample_frequency":1, "suppress_unchanged":"", "max_silent_interval":0} ],
                                    // path: Path specification for elements of OpenConfig data models

                                    // filter: Regular expression to be used in filtering state leaves

                                    // suppress_unchanged: If this is set to true, the target device will only send
                                    // updates to the collector upon a change in data value

                                    // max_silent_interval: Maximum time in ms the target device may go without sending
                                    // a message to the collector. If this time expires with
                                    // suppress-unchanged set, the target device must send an update
                                    // message regardless if the data values have changed.

                                    // sample_frequncy: Time in ms between collection and transmission of the
                                    // specified data to the collector platform. The target device
                                    // will sample the corresponding data (e.g,. a counter) and
                                    // immediately send to the collector destination.
                                    // If sample-frequency is set to 0, then the network device
                                    // must emit an update upon every datum change.

                                  "input":{"collector_list":[{"address":"10.92.232.121", "port":50051}]},
                                    // address: IP address of collector endpoint
                                    // port: Transport protocol port number for the collector destination.

                                  "additional_config":{"limit_records":1, "limit_time_seconds":1}
                                    // limit_records: limit the number of records sent in the stream
                                    // limit_time_seconds: limit the time the stream remains open
                                }
                  }
                ]
        }
    ```
    
    ## getSubscription.json
        {
          "dut_list":
               [
                {
                  "ip": "hanoi",
                  "port":50051,
                  "session_log":"grpc.session",
                  "log_file":"grpc.data", //grpc data log header
                  "oc_rpc" : ["subscriptionsGet"],
                  "subscriptionsGet": { "id": 3 },
                  // id is hte subscription_id getting from subscription request
                }
               ] 
        }

    ## getOperationalState.json
        {
          "dut_list":
               [
                {
                  "ip": "hanoi",
                  "port":50051,
                  "session_log":"grpc.session",
                  "oc_rpc" : ["operationalStateGet"],
                  "subscriptionsGet": { "id": 3 },
                  "operationalStateGet": { "verbosity": "DETAIL", "id": 3 },
                  //verbosity can be one of DETAIL, TERSE, BRIEF
                  // id is hte subscription_id getting from subscription request
                }
               ]
        }

    ## getDataEncoding.json 
        {
          "dut_list":
               [
                {
                  "ip": "hanoi",
                  "port":50051,
                  "session_log":"grpc.session",
                  "oc_rpc" : ["getDataEncodings"],
                  "getDataEncodings": {  }
                  // Parameters may extend in the future
                }
               ]
        }

    ## unsubscription.json
        {
          "dut_list":
               [
                {
                  "ip": "hanoi",
                  "port":50051,
                  "session_log":"grpc.session",
                  "oc_rpc" : ["unsubscribe"],
                  "unsubscribe": {"id": 3}
                  // id is hte subscription_id getting from subscription request
                }
               ]
        }

# Multithread json config
  Configure multiple DUTs (IP address can be same), the decoder will spawn multithread for grpc connection and decoding the data simultaneously.
  * Below example will spawn 2 threads to hanoi node, one for optics sensor and another for NPU sensor.
  
  ```
    {
      "dut_list":
           [
            {
              "ip": "hanoi",
              "port":50051,
              "session_log":"grpc.session",
              "log_head":"grpc.data",
              "oc_rpc" : ["subscribe"],
              "subscribe": {
                              "path_list": [{ "path":"/junos/system/linecard/optics/", "filter":"", "sample_frequency":1, "suppress_unchanged":"", "max_silent_interval":0} ],
                              "input":{"collector_list":[{"address":"10.92.232.121", "port":50051}]},
                              "additional_config":{"limit_records":1, "limit_time_seconds":1}
                        }
            },
            {
              "ip": "hanoi",
              "port":50051,
              "session_log":"grpc.session",
              "log_head":"grpc.data",
              "oc_rpc" : ["subscribe"],
              "subscribe": {
                              "path_list": [{ "path":"/junos/system/linecard/cpu/memory/", "filter":"", "sample_frequency":1, "suppress_unchanged":"", "max_silent_interval":0} ],
                              "input":{"collector_list":[{"address":"10.92.232.121", "port":50051}]},
                              "additional_config":{"limit_records":1, "limit_time_seconds":1}
                        }
            }
           ]
    }
  ```


