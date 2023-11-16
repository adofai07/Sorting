import tensorflow as tf
from type import RandomizedListGenerator
import tqdm
import random
import numpy as np
import pickle
import os
import sys
import statistics as stt
import copy

print(tf.__version__)
print(tf.config.list_physical_devices('GPU'))

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


act1 = "tanh"
act2 = "sigmoid"
act3 = "linear"

model = tf.keras.Sequential([
    tf.keras.layers.Dense(8, activation=act1, input_shape=(3, )),
    tf.keras.layers.Dense(1, activation=act2)
])


model.compile(
    optimizer=tf.keras.optimizers.Adam(),
    loss="mse",
    metrics=[
            tf.keras.metrics.MeanAbsoluteError(name="MAerr"),
            # tf.keras.metrics.MeanAbsolutePercentageError(name="MAPerr")
        ]
)

DATA = 1_000_000
EPOCHS = 500
N = 1000
MEAN_RANGE = 10000
SIGMA_RANGE = 10000

I_O = list()

for i in tqdm.trange(DATA, position=0, unit_scale=True):
    l = RandomizedListGenerator.Float.normal(N, random.uniform(-MEAN_RANGE, MEAN_RANGE), random.uniform(0, SIGMA_RANGE))
    ll = copy.deepcopy(l)
    ll.sort()

    idx = random.randrange(0, N)

    I_O.append(
        (
            (stt.mean(l), stt.stdev(l), l[idx]),
            ll.index(l[idx]) / N
        )
    )

random.shuffle(I_O)

save(I_O, "Dataset1")

inputs = np.asarray([i[0] for i in I_O])
outputs = np.asarray([i[1] for i in I_O])

print(F"\nData: {sys.getsizeof(inputs) :,} bytes (input), {sys.getsizeof(outputs) :,} bytes (output)\n")

history = model.fit(
    inputs,
    outputs,
    epochs=EPOCHS,
    batch_size=EPOCHS
)

print(model.optimizer)

# tf.keras.models.save_model(model, "C:/SSHS/codes/Data/SortingAIModel.hdf5", overwrite=True, save_format="hdf5")
