using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using PubNubAPI;

public class Countdown : MonoBehaviour {
	public GameObject Label;
	public int power = 0;
	private GUIText powercount; // The label.

	public static PubNub pubnub;

	// Use this for initialization
	void Start () {
		powercount = gameObject.GetComponent<GUIText>(); 

		PNConfiguration pnConfiguration = new PNConfiguration(); // Start PubNub 
        pnConfiguration.PublishKey = "pub-c-ae388464-6b8a-430e-be0a-64377c198dda"; // YOUR PUBLISH KEY HERE. 
        pnConfiguration.SubscribeKey = "sub-c-77c1dde4-dc65-11e8-b7c4-3e16c06ff365"; // YOUR SUBSCRIBE KEY HERE.
        pubnub = new PubNub(pnConfiguration);
	}
	
	// Update is called once per frame
	void Update () {
		powercount.text = power+" / 8";
		if ( power == 8 ) {
			pubnub.Publish()
                .Channel("tp") // Send a message to the channel for the game object.
                .Message("l2") // Send the UUID for this client.
                .Async((result, status) => {    
                    if (!status.Error) {
                        Debug.Log(string.Format("Publish Timetoken: {0}", result.Timetoken));
                    } else {
                        Debug.Log(status.Error);
                        Debug.Log(status.ErrorData.Info);
                    }
                });
			// next scene
		}
	}
}
