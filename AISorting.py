from type import RandomizedListGenerator
import pickle
import tensorflow as tf
import numpy as np

def save(data, thread=0):
    with open(FR"C:\SSHS\codes\Data\Sorting{thread}.adofai", "wb+") as f:
        pickle.dump(data, f)

def load(thread=0):
    while True:
        try:
            with open(FR"C:\SSHS\codes\Data\Sorting{thread}.adofai", "rb") as f:
                return pickle.load(f)
            
        except:
            ...

model = tf.keras.models.load_model("C:/SSHS/codes/Data/SortingAIModel.hdf5")

N = 10000
MEAN = 0
STDEV = 1
L = RandomizedListGenerator.Float.normal(N, MEAN, STDEV)
LL = [None for _ in range(N)]

print(model.predict(np.asarray([np.array([MEAN, STDEV, L[i]]) for i in range(N)])))