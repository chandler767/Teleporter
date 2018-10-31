using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.MagicLeap;
using UnityEngine.UI;
using PubNubAPI;

public class ControlSelection : MonoBehaviour {
    Color[] colors = new Color[6];
    private int level = 1;
    private int lastColor;
    private int currentColor;
    private bool isColor = false;
    private float timeLeft = 1.0f;
    
    public Text matchCount;
    public static PubNub pubnub;

    void Start () {
        MLInput.Start(); // Start input controller.
        MLInput.OnTriggerDown += HandleOnTriggerDown; // Get trigger down event.
        colors[0] = Color.white;
        colors[1] = Color.red;
        colors[2] = Color.green;
        colors[3] = Color.blue;
        colors[4] = Color.yellow;
        colors[5] = Color.magenta;
        PNConfiguration pnConfiguration = new PNConfiguration(); // Start PubNub 
        pnConfiguration.PublishKey = "pub-c-ae388464-6b8a-430e-be0a-64377c198dda"; // YOUR PUBLISH KEY HERE. 
        pnConfiguration.SubscribeKey = "sub-c-77c1dde4-dc65-11e8-b7c4-3e16c06ff365"; // YOUR SUBSCRIBE KEY HERE.
        pubnub = new PubNub(pnConfiguration);
    }
    
    void OnDestroy () {
        MLInput.OnTriggerDown -= HandleOnTriggerDown;
        MLInput.Stop();
    }

    void Update () {
        timeLeft -= Time.deltaTime;
        if ( timeLeft < 0 ) {
            lastColor = currentColor;
            currentColor = Random.Range(0, 5);
            if (lastColor == currentColor) { // Ensure the color always changes from the last value.
                if (currentColor > 0) {
                    currentColor = currentColor-1;
                } else if (currentColor < 5) {
                    currentColor = currentColor+1;
                }
            }
            if (level == 1) {
                timeLeft = 1.30f;
            } else if (level == 2 ) {
                timeLeft = 0.95f;
            } else if (level == 3 ) {
                timeLeft = 0.60f;
            }
            GetComponent<Renderer>().material.color = colors[currentColor];
        }
    }

    void HandleOnTriggerDown(byte controllerId, float value) {
        if (currentColor == level) {
            matchCount.text = level+" / 3"; // Update countdown.
            if (level == 1) {
                pubnub.Publish()
                    .Channel("tp")
                    .Message("l2")
                    .Async((result, status) => {    
                        if (!status.Error) {
                            Debug.Log(string.Format("Publish Timetoken: {0}", result.Timetoken));
                        } else {
                            Debug.Log(status.Error);
                            Debug.Log(status.ErrorData.Info);
                        }
                    });
            } else if (level == 2) {
                pubnub.Publish()
                    .Channel("tp")
                    .Message("l3")
                    .Async((result, status) => {    
                        if (!status.Error) {
                            Debug.Log(string.Format("Publish Timetoken: {0}", result.Timetoken));
                        } else {
                            Debug.Log(status.Error);
                            Debug.Log(status.ErrorData.Info);
                        }
                    });
            } else if (level == 3) {
                pubnub.Publish()
                    .Channel("tp")
                    .Message("app")
                    .Async((result, status) => {    
                        if (!status.Error) {
                            Debug.Log(string.Format("Publish Timetoken: {0}", result.Timetoken));
                        } else {
                            Debug.Log(status.Error);
                            Debug.Log(status.ErrorData.Info);
                        }
                    });
                // Game over - win
            }
            level = level+1;
        } else {
            // Back to L1
            level = 1;
            matchCount.text = "0 / 3"; // Update countdown.
            pubnub.Publish()
                .Channel("tp")
                .Message("l1")
                .Async((result, status) => {    
                    if (!status.Error) {
                        Debug.Log(string.Format("Publish Timetoken: {0}", result.Timetoken));
                    } else {
                        Debug.Log(status.Error);
                        Debug.Log(status.ErrorData.Info);
                    }
                });
        }
    }
}