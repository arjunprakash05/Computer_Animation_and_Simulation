# SIG Skeleton Definition
# Original file created by Yazhou Huang

KnSkeleton

name hdman

skeleton
root Hips
{ offset 0 0 0
  channel XPos 0 free
  channel YPos 0 free
  channel ZPos 0 free
  channel Quat

  joint LeftUpLeg
  { offset 4.06525 -3.90732 0.41711

    channel Quat
    prerot axis 0.57735 0.57735 -0.57735 ang 120
    postrot axis -0.57735 -0.57735 0.57735 ang 120

    joint LeftLeg
    { offset 0.00023 -18.4821 0.00367

      channel Quat
      prerot axis 0.57735 0.57735 -0.57735 ang 120
      postrot axis -0.57735 -0.57735 0.57735 ang 120

      joint LeftFoot
      { offset -0.00172 -15.2898 -0.02629

        channel Quat
        prerot axis 0.57735 0.57735 -0.57735 ang 120
        postrot axis -0.57735 -0.57735 0.57735 ang 120

        joint LeftToeBase
        { offset 0.36743 -3.19131 5.54287
		  channel Quat

          joint LeftToeBase2
          { offset 0.08751 0.04849 1.36758
		    channel Quat

            joint LeftToeBase3
            { offset 0.07484 0.06785 1.16707
            }
          }
        }
      }
    }
  }

  joint RightUpLeg
  { offset -4.06526 -3.90731 0.41712

    channel Quat
    prerot axis 0.57735 0.57735 -0.57735 ang 120
    postrot axis -0.57735 -0.57735 0.57735 ang 120

    joint RightLeg
    { offset -0.00029 -18.4821 0.0044

      channel Quat
      prerot axis 0.57735 0.57735 -0.57735 ang 120
      postrot axis -0.57735 -0.57735 0.57735 ang 120

      joint RightFoot
      { offset 0.0016 -15.2898 -0.02569

        channel Quat
        prerot axis 0.57735 0.57735 -0.57735 ang 120
        postrot axis -0.57735 -0.57735 0.57735 ang 120

        joint RightToeBase
        { offset -0.3542 -3.19109 5.54386
		  channel Quat

          joint RightToeBase2
          { offset -0.08424 0.04854 1.36778
		    channel Quat

            joint RightToeBase3
            { offset -0.07205 0.0679 1.16725
            }
          }
        }
      }
    }
  }

  joint Spine
  { offset 1e-005 4.46517 -0.10224

    channel Quat

    joint Spine1
    { offset 1e-005 4.46212 -0.1824

      channel Quat

      joint Spine2
      { offset 0 4.37937 -0.881

        channel Quat

        joint Spine3
        { offset 1e-005 4.68286 0.21414
		  channel Quat

          joint Neck
          { offset 0 1.76964 0.82454
		    channel Quat

            joint Head
            { offset 0 1.6961 0.93145

              channel Quat

              joint Head_End
              { offset 1e-005 7.8375 1.52603
              }
            }
          }

          joint LeftShoulder
          { offset 1.19381 -0.75881 -0.02768
		    channel Quat

            joint LeftArm
            { offset 5.18779 -2e-005 1e-005

              channel Quat axis 1 0 0 ang 0.0395647
              prerot axis 0 1 0 ang 90
              postrot axis 0 -1 0 ang 90

              joint LeftForeArm
              { offset 12.7364 -4e-005 2e-005

                channel Quat axis 1 0 0 ang 0.0395647
                prerot axis 0 1 0 ang 90
                postrot axis 0 -1 0 ang 90

                joint LeftHand
                { offset 9.21452 -2e-005 1e-005

                  channel Quat axis 1 0 0 ang 0.0395647
                  prerot axis 0 1 0 ang 90
                  postrot axis 0 -1 0 ang 90

                  joint LeftHandIndex1
                  { offset 3.59952 0.16811 0.81096

                    joint LeftHandIndex2
                    { offset 1.75897 0 0

                      joint LeftHandIndex3
                      { offset 1.00116 -1e-005 0

                        joint LeftHandIndex4
                        { offset 1.25927 0 0
                        }
                      }
                    }
                  }

                  joint LeftHandMiddle1
                  { offset 3.47772 0.19435 -0.03772

                    joint LeftHandMiddle2
                    { offset 1.8807 -1e-005 0

                      joint LeftHandMiddle3
                      { offset 1.11052 0 0

                        joint LeftHandMiddle4
                        { offset 1.2862 0 0
                        }
                      }
                    }
                  }

                  joint LeftHandPinky1
                  { offset 3.18344 -0.35041 -1.61046

                    joint LeftHandPinky2
                    { offset 1.17265 0 0

                      joint LeftHandPinky3
                      { offset 0.85521 0 0

                        joint LeftHandPinky4
                        { offset 1.11796 0 0
                        }
                      }
                    }
                  }

                  joint LeftHandRing1
                  { offset 3.39806 -0.02715 -0.86476

                    joint LeftHandRing2
                    { offset 1.86271 0 0

                      joint LeftHandRing3
                      { offset 0.98359 0 0

                        joint LeftHandRing4
                        { offset 1.08973 0 0
                        }
                      }
                    }
                  }

                  joint LeftHandThumb1
                  { offset 0.98339 -0.38128 1.25818

                    joint LeftHandThumb2
                    { offset 1e-005 0.00861 1.66202

                      joint LeftHandThumb3
                      { offset -1e-005 0.00553 1.06878

                        joint LeftHandThumb4
                        { offset 0 0.00625 1.2068
                        }
                      }
                    }
                  }
                }
              }
            }
          }

          joint RightShoulder
          { offset -1.19381 -0.75881 -0.02767
		    channel Quat

            joint RightArm
            { offset -5.18779 1e-005 -1e-005

              channel Quat axis 1 0 0 ang 0.0395647
              prerot axis 0 -1 0 ang 90
              postrot axis 0 1 0 ang 90

              joint RightForeArm
              { offset -12.7364 3e-005 -2e-005

                channel Quat axis 1 0 0 ang 0.0395647
                prerot axis 0 -1 0 ang 90
                postrot axis 0 1 0 ang 90

                joint RightHand
                { offset -9.21452 2e-005 -1e-005

                  channel Quat axis 1 0 0 ang 0.0395647
                  prerot axis 0 -1 0 ang 90
                  postrot axis 0 1 0 ang 90

                  joint RightHandIndex1
                  { offset -3.59952 0.16814 0.81095
				    channel Quat

                    joint RightHandIndex2
                    { offset -1.75897 1e-005 0
					  channel Quat

                      joint RightHandIndex3
                      { offset -1.00116 0 0
					    channel Quat

                        joint RightHandIndex4
                        { offset -1.25928 0 0
                        }
                      }
                    }
                  }

                  joint RightHandMiddle1
                  { offset -3.47772 0.19437 -0.03773
				    channel Quat

                    joint RightHandMiddle2
                    { offset -1.8807 0 0
					  channel Quat

                      joint RightHandMiddle3
                      { offset -1.11052 0 0
					    channel Quat

                        joint RightHandMiddle4
                        { offset -1.2862 0 0
                        }
                      }
                    }
                  }

                  joint RightHandPinky1
                  { offset -3.18343 -0.35039 -1.61047
				    channel Quat

                    joint RightHandPinky2
                    { offset -1.17265 0 0
					  channel Quat

                      joint RightHandPinky3
                      { offset -0.8552 0 0
					    channel Quat

                        joint RightHandPinky4
                        { offset -1.11796 0 0
                        }
                      }
                    }
                  }

                  joint RightHandRing1
                  { offset -3.39806 -0.02712 -0.86477
				    channel Quat

                    joint RightHandRing2
                    { offset -1.86271 0 0
					  channel Quat

                      joint RightHandRing3
                      { offset -0.9836 1e-005 0
					    channel Quat

                        joint RightHandRing4
                        { offset -1.08973 1e-005 0
                        }
                      }
                    }
                  }

                  joint RightHandThumb1
                  { offset -0.9834 -0.38128 1.25818
				    channel Quat

                    joint RightHandThumb2
                    { offset 0 0.00861 1.66202
					  channel Quat

                      joint RightHandThumb3
                      { offset 0 0.00553 1.06878
					    channel Quat

                        joint RightHandThumb4
                        { offset 0 0.00625 1.2068
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

end
